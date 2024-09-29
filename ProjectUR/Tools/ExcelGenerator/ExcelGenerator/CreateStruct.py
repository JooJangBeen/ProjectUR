import os
import sys
import csv
import subprocess

# 프로젝트 명
project_name = "ProjectUR"

# CSV 파일이 존재하는 폴더 경로
csv_path = "Content/" + "Data/" + "CSV"

# c++ struct 를 저장할 폴더 경로 ->
struct_save_path = "Source/" + project_name + "/14_Data"

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
        return "FString"


# 스크립트 작성 함수
def create_struct():
    print("####### CSV와 C++의 경로를 지정하기 위해 추가된 코드 ####### ")
    # 현재 폴더 경로; 작업 폴더 기준

    #PyInstaller같은 도구로 실행 파일을 만들경우 파이썬 exe 파일 경로는 여기 os.path.dirname(sys.executable)
    #도구를 사용하여 배포하지 않고 일반 파이썬 파일의 경로는 여기 os.path.dirname(os.path.realpath(__file__))

    # 현재 스크립트의 경로를 가져옴
    current_path = os.path.dirname(sys.executable)

    # 제거할 문자열
    target_string = r"Tools\ExcelGenerator\ExcelGenerator\dist"

    # 경로에 target_string이 포함되어 있는지 확인하고 제거
    if target_string in current_path:
        # target_string이 나타나는 위치까지 경로를 잘라냄
        new_path = current_path.replace(target_string, "").rstrip(os.sep)

        # 경로 구분자가 없는 경우 추가
        if not new_path.endswith(os.sep):
            new_path += os.sep

        # 경로의 모든 '\'를 '/'로 변환
        new_path = new_path.replace("\\", "/")

        print("수정된 경로:", new_path)
    else:
        new_path = current_path
        print("문자열을 찾을 수 없습니다.")

    # 현재 파일의 폴더 경로; 작업 파일 기준
    csv_folder = new_path + csv_path
    struct_save_folder = new_path + struct_save_path

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

# 실행 부분
create_struct()
print("********* C++ Struct Generator Closed. **********")