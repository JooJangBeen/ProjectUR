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
temp_csv_path = unreal.SystemLibrary.get_project_directory() + "Temp_TableGenerator.csv"

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
    with open(csv_path, 'r',encoding='euc-kr') as origin:
        csv_reader = csv.reader(origin)
        id_row_index = -1

        for index, row in enumerate(csv_reader):
            origin_rows.append(row)
            if str(row[0]).lower() == "id":
                id_row_index = index

        if id_row_index == -1:
            unreal.log_error("Cannot found Id column.")
            return

    raw_data_rows = []
    for index, row in enumerate(origin_rows):
        if index >= id_row_index:
            raw_data_rows.append(row)

    with open(temp_csv_path, 'w', newline='' ) as temp_csv:
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
        print(csv_file_path)
#############################################Create Table######################################################

# 실행 부분
create_asset()
print("********* Data Table Asset Generator Closed. **********")