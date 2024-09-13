import unreal
import os
import sys
import csv

# 현재는 따로 폴더 생성 기능 제공 안함.

# 프로젝트 명
project_name = "ProjectUR"

# CSV 파일이 존재하는 폴더 경로
csv_folder = unreal.SystemLibrary.get_project_directory() + "Content/" + "Data/" + "CSV"

# c++ struct 를 저장할 폴더 경로 ->
struct_save_folder = unreal.SystemLibrary.get_project_directory() + "Source/" + project_name + "/14_Data"

# 데이터 테이블 클래스
asset_class = unreal.DataTable

# 데이터 테이블 에셋 저장 경로
asset_path = unreal.SystemLibrary.get_project_directory() + "Content/" + "Data/" + "Table"

# CSV 를 추출해서 순 데이터만 존재하는 임시파일 생성
temp_csv_path = unreal.SystemLibrary.get_project_directory() + "Content/" + "Data/" + "Temp_TableGenerator.csv"

#############################################Create Struct######################################################
# 개행 함수
def next_line(file):
    file.write("\n")


# 타입 선별 함수
def get_unreal_type(type):
    str_type = str(type).lower()

    if str_type == "int" or str_type == "int32":
        return "int32"
    elif str_type == "float" or str_type == "float32":
        return "float"
    elif str_type == "string" or str_type == "fstring":
        return "FString"
    elif str_type == "bool" or str_type == "boolean":
        return "bool"
    elif str_type == "vector" or str_type == "vector3":
        return "FVector"
    elif str_type == "rotator" or str_type == "rotator":
        return "FRotator"
    elif str_type == "text":
        return "FText"
    elif str_type == "color" or str_type == "coloru8":
        return "FLinearColor"
    else:
        unreal.log_error(str_type + " << This type is not allowed. It will change to \'FString\'.")
        return "FString"


# 스크립트 작성 함수
def create_struct():
    print("#######   Data Table C++ Struct Generator Started!     #######")
    print("######    Target CSV Folder : " + csv_folder)
    print("-")
    # csv_folder 내부의 모든 파일 리스트 검출
    file_list = os.listdir(csv_folder)

    csv_file_list = []
    # CSV 가 아닌 것 걸러내기
    for file in file_list:
        if file.endswith(".csv"):
            csv_file_list.append(file)

    if len(csv_file_list) == 0:
        unreal.log_error("There's no CSV file in folder : " + path.csv_folder)
        sys.exit(0)

    print("----------- CSV File List ------------")
    print("-")
    # 반복문 시작 : 하나 씩 변환 시작
    index = 1
    for file in csv_file_list:
        print("(" + str(index) + ") " + file)
        index += 1

    print("-")
    for file in csv_file_list:
        print("-")
        print("::::::::::::: Start making [" + file + "] ::::::::::::::")
        # csv 파일 경로 추출
        csv_file_path = os.path.join(csv_folder, file)

        # 먼저 C++ 부터 작성
        print("----------    Writing C++ Struct row table...   -------------")
        print("-")
        # CSV 를 행 별로 저장
        rows = []
        # 파일 열고 행 별로 rows 에 담는다
        with open(csv_file_path, 'r', encoding='euc-kr') as csvfile:
            csv_reader = csv.reader(csvfile)
            for row in csv_reader:
                print(row)
                rows.append(row)

        # 행이 아무것도 없다면 종료
        if len(rows) == 0:
            unreal.log_error("CSV row count is 0")
            continue

        # Id column_name은 2번째 인덱스기 때문에 1
        column_name_row_index = 1

        type_name_list = []
        column_name_list = []
        # 타입 이름과 컬럼 이름 수집
        column_name_row = rows[column_name_row_index]
        for index, column_name in enumerate(column_name_row):
            # '#' 으로 시작하는 칼럼은 추가하지 않는다.
            if not column_name.startswith("#"):
                # Id 칼럼 위 행은 타입 행이므로 -1 한 위치에서 타입 이름을 저장.
                # rows[Id 칼럼의 윗 행 인덱스][현재 열 인덱스]
                type_row = rows[column_name_row_index - 1]
                type_name_list.append(type_row[index])
                column_name_list.append(column_name)

        # 타입 갯수와 칼럼 열 갯수가 다르면 경고 후 스킵
        if len(type_name_list) != len(column_name_list):
            print("Type name count and column name count is not correct : " + len(type_name_list) + "/" + len(
                column_name_list))
            continue
        # 파일명 추출
        file_name = os.path.basename(csv_file_path)
        file_name = str(file_name).split('.')[0]
        # 파일 작성 시작
        with open(struct_save_folder + "/F" + file_name + ".h", 'w', encoding='utf8') as c_file:
            next_line(c_file)
            c_file.writelines("# pragma once\n")
            next_line(c_file)
            c_file.writelines("#include \"Engine/DataTable.h\"\n")
            c_file.writelines("#include \"F" + file_name + ".generated.h\"\n")
            next_line(c_file)
            c_file.writelines("USTRUCT(Blueprintable)\n")
            c_file.writelines("struct F" + file_name + " : public FTableRowBase\n")
            c_file.writelines("{\n")
            c_file.writelines("\tGENERATED_USTRUCT_BODY()\n")
            next_line(c_file)
            c_file.writelines("public:\n")
            next_line(c_file)
            # 변수 선언
            for index, value in enumerate(column_name_list):
                # id 변수는 선언하지 않는다 -> 기본적으로 Row Name 칼럼이 Id 역할을 해주기 때문 만약 이 코드 없애면 첫번째 행이 RowName으로 들어가서 이상하게 보인다.
                if str(value).lower() == "id":
                    continue
                c_file.writelines("\tUPROPERTY(EditAnywhere, BlueprintReadWrite)\n")
                c_file.writelines("\t" + get_unreal_type(type_name_list[index]) + " " + str(value) + ";\n")
                next_line(c_file)

            c_file.writelines("};\n")

        # struct_path : ex) "/Script/project_name.TestTable"
        # unreal_struct_path = "/Script/" + project_name + "." + file_name

#############################################Create Struct######################################################

#############################################Create Table######################################################
# struct_path : ex) "/Script/RottenPotato.TestTable"
# 데이터 테이블 에셋 생성 함수
def create_data_table_asset(csv_path):
    # 파일명
    file_name = str(os.path.basename(csv_path)).split('.')[0]
    # 데이터 테이블 파일명
    asset_name = "DT_" + file_name
    # base struct 스크립트 경로
    unreal_struct_path = "/Script/" + project_name + "." + file_name

    print("--------- Creating data table asset..." + " Struct path : " + unreal_struct_path + " ----------")
    print("-")
    # 데이터 테이블 구조체
    asset_factory = unreal.DataTableFactory()
    asset_factory.struct = unreal.load_object(None, unreal_struct_path)
    if asset_factory.struct is None:
        unreal.log_error("Asset factory struct is none.")
        return

    # CSV 를 추출해서 순 데이터만 존재하는 임시파일 생성
    origin_rows = []
    with open(csv_path, 'r') as origin:
        csv_reader = csv.reader(origin)
        id_row_index = sys.maxsize

    raw_data_rows = []
    for index, row in enumerate(origin_rows):
        if index >= id_row_index:
            raw_data_rows.append(row)

    with open(temp_csv_path, 'w') as temp_csv:
        for row in raw_data_rows:
            for index, data in enumerate(row):
                temp_csv.write(data)
                if index != len(row):
                    temp_csv.write(",")
            temp_csv.write("\n")

    csv_factory = unreal.CSVImportFactory()
    csv_factory.automated_import_settings.import_row_struct = asset_factory.struct

    task = unreal.AssetImportTask()
    task.filename = temp_csv_path
    task.destination_name = asset_name
    task.destination_path = asset_path
    task.replace_existing = True
    task.automated = True
    task.save = True
    task.factory = csv_factory

    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])

    try:
        os.remove(temp_csv_path)
    except FileNotFoundError:
        return
    except Exception as e:
        unreal.log_error(e)


# 시작 함수
def create_asset():
    print("#######   Data Table Asset Generator Started!     #######")
    print("######    Target CSV Folder : " + csv_folder)
    print("-")
    # csv_folder 내부의 모든 파일 리스트 검출
    file_list = os.listdir(csv_folder)

    csv_file_list = []
    # CSV 가 아닌 것 걸러내기
    for file in file_list:
        if file.endswith(".csv"):
            csv_file_list.append(file)

    if len(csv_file_list) == 0:
        unreal.log_error("There's no CSV file in folder : " + csv_folder)
        sys.exit(0)

    print("----------- CSV File List ------------")
    print("-")
    # 반복문 시작 : 하나 씩 변환 시작
    index = 1
    for file in csv_file_list:
        print("(" + str(index) + ") " + file)
        index += 1

    print("-")
    for file in csv_file_list:
        print("-")
        print("::::::::::::: Start making [" + file + "] ::::::::::::::")
        # csv 파일 경로 추출
        csv_file_path = os.path.join(csv_folder, file)
        create_data_table_asset(csv_file_path)
#############################################Create Table######################################################

# 실행 부분
create_struct()
print("********* C++ Struct Generator Closed. **********")
#create_asset()
#print("********* Data Table Asset Generator Closed. **********")