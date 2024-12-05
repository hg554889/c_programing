#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include <windows.h>

// 색상 설정 함수 (Windows)
void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 에러 처리를 위한 함수
void finish_with_error(MYSQL* con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

// 문자열 길이를 계산하는 함수 (한글 고려)
int utf8_strlen(const char* str) {
    int len = 0;
    int i = 0;
    while (str[i]) {
        if ((str[i] & 0xC0) != 0x80) {
            len++;
        }
        i++;
    }
    return len;
}
// 프로그래밍 언어 선택 메뉴
void print_language_menu() {
    set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n============================\n");
    printf("  프로그래밍 언어 버전 정보\n");
    printf("============================\n");
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("1. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("C"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("2. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("C++"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("3. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("C#"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("4. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("Ruby"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("5. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("Java"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("6. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("Python"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("7. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("JavaScript"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("8. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("TypeScript"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("9. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("R"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("10. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("SQL"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    set_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("0. 뒤로 가기\n");
    set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("============================\n");
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("번호를 선택하세요: ");
}

// IDE 선택 메뉴
void print_ide_menu() {
    set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n============================\n");
    printf("          IDE 정보\n");
    printf("============================\n");
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("1. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("Pycharm"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("2. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("IntelliJ"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("3. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("GoLand"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("4. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("Rider"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("5. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("CLion"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("6. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("RustRover"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("7. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("Webstrom"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("8. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("RubyMine"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
    printf("0. 뒤로 가기\n");
    set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("============================\n");
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("번호를 선택하세요: ");
}

void print_data(MYSQL_RES* result) {
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    int* col_widths = (int*)malloc(num_fields * sizeof(int));
    int i;

    // 각 열의 최대 너비 계산
    for (i = 0; i < num_fields; i++) {
        col_widths[i] = utf8_strlen(mysql_fetch_field(result)->name); // 헤더 너비
    }

    mysql_data_seek(result, 0); // 데이터 포인터를 처음으로 되돌림
    while ((row = mysql_fetch_row(result))) {
        for (i = 0; i < num_fields; i++) {
            int len = utf8_strlen(row[i] ? row[i] : "NULL");
            if (len > col_widths[i]) {
                col_widths[i] = len;
            }
        }
    }

    mysql_data_seek(result, 0); // 데이터 포인터를 처음으로 되돌림

    // 헤더 출력
    set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("┌");
    for (i = 0; i < num_fields; i++) {
        for (int j = 0; j < col_widths[i] + 2; j++) {
            printf("─");
        }
        if (i < num_fields - 1) {
            printf("┬");
        }
    }
    printf("┐\n");

    printf("│");
    mysql_field_seek(result, 0); // 필드 포인터를 처음으로 되돌림
    for (i = 0; i < num_fields; i++) {
        MYSQL_FIELD* field = mysql_fetch_field(result);
        set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // 노란색으로 변경
        printf(" %-*s ", col_widths[i], field->name);
        set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        if (i < num_fields - 1) {
            printf("│");
        }
    }
    printf("│\n");

    printf("├");
    for (i = 0; i < num_fields; i++) {
        for (int j = 0; j < col_widths[i] + 2; j++) {
            printf("─");
        }
        if (i < num_fields - 1) {
            printf("┼");
        }
    }
    printf("┤\n");

    // 데이터 출력
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    while ((row = mysql_fetch_row(result))) {
        printf("│");
        for (i = 0; i < num_fields; i++) {
            printf(" %-*s ", col_widths[i], row[i] ? row[i] : "NULL");
            if (i < num_fields - 1) {
                printf("│");
            }
        }
        printf("│\n");
    }

    set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("└");
    for (i = 0; i < num_fields; i++) {
        for (int j = 0; j < col_widths[i] + 2; j++) {
            printf("─");
        }
        if (i < num_fields - 1) {
            printf("┴");
        }
    }
    printf("┘\n");
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    free(col_widths);
}

int main(int argc, char** argv) {

    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // MySQL 연결 설정 (user, password, dbname은 실제 값으로 변경)
    if (mysql_real_connect(con, "localhost", "root", "Mysql04078**", "MyNewDatabase", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    while (1) {
        int main_choice, sub_choice; // main_choice = 카테고리, sub_choice = 선택된 카테고리의 세부 항복
        printf("\n============================\n");
        printf("      카테고리 선택\n");
        printf("============================\n");
        printf("1. 프로그래밍 언어\n");
        printf("2. IDE\n");
        printf("0. 종료\n");
        printf("============================\n");
        printf("번호를 선택하세요: ");
        scanf_s("%d", &main_choice, sizeof(main_choice));

        // 프로그램 종료
        if (main_choice == 0) {
            mysql_close(con);
            exit(0);
        }

        switch (main_choice) {
        case 1: // 프로그래밍 언어 선택
            print_language_menu(); // 프로그램 언어 메뉴 출력
            scanf_s("%d", &sub_choice, sizeof(sub_choice));

            if (sub_choice == 0) continue;  // 뒤로 가기
           
            char query_lang[256];

            switch (sub_choice) {
            case 1: // C
                snprintf(query_lang, sizeof(query_lang), "SELECT version, date, documentation FROM C");
                break;
            case 2: // C++
                snprintf(query_lang, sizeof(query_lang), "SELECT version, date, documentation FROM Cpp");
                break;
            case 3: // C#
                snprintf(query_lang, sizeof(query_lang), "SELECT version, date, documentation FROM C_Sharp");
                break;
            case 4: // RUBY
                snprintf(query_lang, sizeof(query_lang), "SELECT version, date, documentation FROM Ruby");
                break;
            case 5: // JAVA
                snprintf(query_lang, sizeof(query_lang), "SELECT version, date, documentation FROM Java");
                break;
            case 6: // PYTHON
                snprintf(query_lang, sizeof(query_lang), "SELECT version, date, documentation FROM PYTHON");
                break;
            case 7: // JavaScript
                snprintf(query_lang, sizeof(query_lang), "SELECT version, date, documentation FROM JavaScript");
                break;
            case 8: // Type Script
                snprintf(query_lang, sizeof(query_lang), "SELECT version, date, documentation FROM TypeScript");
                break;
            case 9: // R
                snprintf(query_lang, sizeof(query_lang), "SELECT version, date, documentation FROM R");
                break;
            case 10: // SQL
                snprintf(query_lang, sizeof(query_lang), "SELECT version, date, documentation FROM MySQL");
                break;
            case 0:
                mysql_close(con);
                exit(0);
            default:
                printf("잘못된 선택입니다.\n");
                continue; // switch 문 처음으로 이동
            }
            if (mysql_query(con, query_lang)) {
                finish_with_error(con);
            }
            MYSQL_RES* lang_result = mysql_store_result(con);
            if (lang_result == NULL) {
                finish_with_error(con);
            }
            // 결과 출력
            print_data(lang_result);
            mysql_free_result(lang_result);
            break;

        case 2: // IDE 선택
            print_ide_menu();
            scanf_s("%d", &sub_choice, sizeof(sub_choice));

            if (sub_choice == 0) continue; // 뒤로 가기
            
            char query_ide[256];

            switch (sub_choice) {
            case 1:
                snprintf(query_ide, sizeof(query_ide), "SELECT language, Description FROM IDE WHERE name = 'Pycharm'");
                break;
            case 2:
                snprintf(query_ide, sizeof(query_ide), "SELECT language, Description FROM IDE WHERE name = 'IntelliJ'");
                break;
            case 3:
                snprintf(query_ide, sizeof(query_ide), "SELECT language, Description FROM IDE WHERE name = 'GoLand'");
                break;
            case 4:
                snprintf(query_ide, sizeof(query_ide), "SELECT language, Description FROM IDE WHERE name = 'Rider'");
                break;
            case 5:
                snprintf(query_ide, sizeof(query_ide), "SELECT language, Description FROM IDE WHERE name = 'CLion'");
                break;
            case 6:
                snprintf(query_ide, sizeof(query_ide), "SELECT language, Description FROM IDE WHERE name = 'RustRover'");
                break;
            case 7:
                snprintf(query_ide, sizeof(query_ide), "SELECT language, Description FROM IDE WHERE name = 'WebStrom'");
                break;
            case 8:
                snprintf(query_ide, sizeof(query_ide), "SELECT language, Description FROM IDE WHERE name = 'RubyMine'");
                break;
            default:
                printf("잘못된 선택입니다.\n");
                continue;
            }
            if (mysql_query(con, query_ide)) {
                finish_with_error(con);
            }
            MYSQL_RES* ide_result = mysql_store_result(con);
            if (ide_result == NULL) {
                finish_with_error(con);
            }
            // 쿼리 결과 출력
            print_data(ide_result);
            mysql_free_result(ide_result);
            break;

        default: // 잘못된 선택 처리
            printf("잘못된 선택입니다.\n");
            break;
        }
    }

    return 0;
}
