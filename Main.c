#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

// 에러 처리를 위한 함수
// MySQL에서 오류가 발생하면 오류 메시지를 출력하고 연결을 종료하며 프로그램을 종료함
void finish_with_error(MYSQL* con) {
    fprintf(stderr, "%s\n", mysql_error(con)); // 오류 메시지 출력
    mysql_close(con); // MySQL 연결 종료
    exit(1); // 프로그램 종료
}

int main() {
    // MySQL 연결 객체 초기화
    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con)); // 초기화 실패 시 오류 메시지 출력
        exit(1); // 프로그램 종료
    }

    // MySQL 서버에 연결
    if (mysql_real_connect(con, "localhost", "root", "kimhungjin88@", "MyNewDatabase", 0, NULL, 0) == NULL) {
        finish_with_error(con); // 연결 실패 시 에러 처리 함수 호출
    }

    // 첫번째 테이블 생성
    //if (mysql_query(con, "CREATE TABLE IF NOT EXISTS TestTable ("
    //    "id INT AUTO_INCREMENT PRIMARY KEY, " // id 필드: 자동 증가, 기본 키
    //    "language VARCHAR(100), " // language 필드: 최대 100자의 문자열
    //    "version VARCHAR(100), "  // version 필드: 최대 100자의 문자열
    //    "date VARCHAR(100))")) { // date 필드 : 최대 100자의 문자열
    //    finish_with_error(con); // 쿼리 실행 실패 시 에러 처리 함수 호출
    //}

    // 두번째 테이블 생성
    //if (mysql_query(con, "CREATE TABLE IF NOT EXISTS TestTable2 ("
    //    "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
    //    "language VARCHAR(100), " // language 필드 : 최대 100자의 문자열
    //    "version VARCHAR(100), " // version 필드 : 최대 100자의 문자열
    //    "date VARCHAR(100))")) { // date 필드 : 최대 100자의 문자열
    //    finish_with_error(con);
    //}

    //// 테이블 삭제
    //if (mysql_query(con, "DROP TABLE IF EXISTS TestTable")) {
    //    finish_with_error(con); // 테이블 삭제 실패 시 에러 처리 함수 호출
    //}
    //printf("Table dropped successfully!\n");

    // 첫 번째 데이터 삽입
    //if (mysql_query(con, "INSERT INTO TestTable (language, version, date) VALUES "
    //    "('python', '3.13', '2024/11/20'), "
    //    "('C', 'C 23', '2023/07/28')")) {
    //    finish_with_error(con); // 데이터 삽입 실패 시 에러 처리 함수 호출
    //}

    printf("Data inserted successfully!\n"); // 데이터 삽입 성공 메시지 출력

    // 첫 번째 데이터 업데이트
    if (mysql_query(con, "UPDATE TestTable SET version = '3.12.8' WHERE language = 'Python'")) {
        // TestTable에서 name이 'Alice'인 행의 age 값을 35로 업데이트
        finish_with_error(con);
    }

    // 두 번째 테이블에 데이터 삽입
    /*if (mysql_query(con, "INSERT INTO TestTable2 (language, version, date) VALUES "
        "('C', 'C17', '2017/01/15'), "
        "('C', 'C23', '2023/07/28')")) {
        finish_with_error(con);
    }

    printf("Data inserted into TestTable2 successfully!\n");*/

    //// 데이터 삭제
    //if (mysql_query(con, "DELETE FROM TestTable WHERE name = 'Alice'")) { // 'Alice'라는 이름의 데이터를 삭제, value에 맞게 수정
    //    finish_with_error(con);
    //}
    //printf("Data deleted successfully!\n");

    // 첫 번째 데이터 조회
    if (mysql_query(con, "SELECT * FROM TestTable")) {
        finish_with_error(con); // 데이터 조회 쿼리 실패 시 에러 처리 함수 호출
    }

    // 쿼리 결과 저장
    MYSQL_RES* result = mysql_store_result(con);

    if (result == NULL) {
        finish_with_error(con); // 결과 저장 실패 시 에러 처리 함수 호출
    }

    // 결과 필드(열) 수 가져오기
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    // 조회된 데이터 출력
    printf("Fetched Data:\n");
    while ((row = mysql_fetch_row(result))) { // 결과를 한 행씩 가져옴
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL"); // 각 열의 데이터를 출력 (NULL은 "NULL"로 표시)
        }
        printf("\n"); // 한 행 출력 완료 후 줄 바꿈
    }

    // 두 번째 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM TestTable2")) {
        finish_with_error(con);
    }

    MYSQL_RES* result2 = mysql_store_result(con);
    if (result2 == NULL) {
        finish_with_error(con);
    }

    printf("Data from TestTable2:\n");
    int num_fields2 = mysql_num_fields(result2);
    MYSQL_ROW row2;
    while ((row2 = mysql_fetch_row(result2))) {
        for (int i = 0; i < num_fields2; i++) {
            printf("%s ", row2[i] ? row2[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result); // 결과 메모리 해제
    mysql_close(con); // MySQL 연결 종료

    return 0; // 프로그램 정상 종료
}
