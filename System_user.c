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
	fprintf(stderr, "%s\n", mysql_error(con)); // 에러 메시지 출력
	mysql_close(con); // MySQL 연결 종료
	exit(1); // 프로그램 종료
}

// 문자열 길이를 계산하는 함수 (한글 고려)
int utf8_strlen(const char* str) {
	int len = 0;
	int i = 0;

	while (str[i]) {
		if ((str[i] & 0xC0) != 0x80) { // UTF-8 문자열의 한 글자씩 계산
			len++;
		}
		i++;
	}

	return len;
}

// 카테고리 선택 메뉴
void print_category_menu() {
	set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // 파란색으로 설정
	printf("\n=============================\n");
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("       카테고리 선택\n");
	set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("=============================\n");
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 기본 색상으로 설정
	printf("1. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("프로그래밍 언어"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n"); // 노란색으로 강조
	printf("2. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("IDE"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
	set_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("0. 종료\n");
	set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("=============================\n");
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("번호를 선택하세요: ");
}

// 프로그래밍 언어 선택 메뉴
void print_language_menu() {
	set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // 녹색으로 설정
	printf("\n=============================\n");
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("  프로그래밍 언어 버전 정보\n");
	set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("=============================\n");
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
	printf("=============================\n");
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("번호를 선택하세요: ");
}

// IDE 선택 메뉴
void print_ide_menu() {
	set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("\n=============================\n");
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("          IDE 정보\n");
	set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("=============================\n");
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("1. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("PyCharm"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
	printf("2. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("IntelliJ"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
	printf("3. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("GoLand"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
	printf("4. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("Rider"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
	printf("5. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("CLion"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
	printf("6. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("RustRover"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
	printf("7. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("WebStorm"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
	printf("8. "); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("RubyMine"); set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); printf("\n");
	set_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("0. 뒤로 가기\n");
	set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("=============================\n");
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("번호를 선택하세요: ");
}

// 데이터 출력 함수
void print_data(MYSQL_RES* result) {
	int num_fields = mysql_num_fields(result); // 결과 집합의 열 개수
	MYSQL_ROW row; // 결과 집합의 한 행을 저장할 변수
	int* col_widths = (int*)malloc(num_fields * sizeof(int)); // 각 열의 최대 너비를 저장할 배열
	int i;

	// 각 열의 최대 너비 계산
	for (i = 0; i < num_fields; i++) {
		col_widths[i] = utf8_strlen(mysql_fetch_field(result)->name); // 헤더 너비
	}

	mysql_data_seek(result, 0); // 데이터 포인터를 처음으로 되돌림

	while ((row = mysql_fetch_row(result))) {
		for (i = 0; i < num_fields; i++) {
			int len = utf8_strlen(row[i] ? row[i] : "NULL"); // 현재 행의 i번째 열의 데이터 길이 계산
			if (len > col_widths[i]) {
				col_widths[i] = len; // 최대 너비 갱신
			}
		}
	}

	mysql_data_seek(result, 0); // 데이터 포인터를 처음으로 되돌림

	// 헤더 출력
	set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // 파란색으로 설정
	printf("┌");
	for (i = 0; i < num_fields; i++) {
		for (int j = 0; j < col_widths[i] + 2; j++) { // 열 너비 + 좌우 공백 1칸씩
			printf("─");
		}
		if (i < num_fields - 1) {
			printf("┬"); // 열 사이 구분자
		}
	}
	printf("┐\n"); // 테이블 상단 경계

	printf("│"); // 좌측 경계
	mysql_field_seek(result, 0); // 필드 포인터를 처음으로 되돌림
	for (i = 0; i < num_fields; i++) {
		MYSQL_FIELD* field = mysql_fetch_field(result); // i번째 열의 필드 정보 가져오기
		set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // 노란색으로 변경
		printf(" %-*s ", col_widths[i], field->name); // 헤더 출력 (좌우 정렬)
		set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // 파란색으로 변경
		if (i < num_fields - 1) {
			printf("│"); // 열 사이 구분자
		}
	}
	printf("│\n"); // 우측 경계

	printf("├"); // 좌측 경계
	for (i = 0; i < num_fields; i++) {
		for (int j = 0; j < col_widths[i] + 2; j++) {
			printf("─");
		}
		if (i < num_fields - 1) {
			printf("┼"); // 열 사이 구분자
		}
	}
	printf("┤\n"); // 우측 경계

	// 데이터 출력
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 기본 색상으로 설정
	while ((row = mysql_fetch_row(result))) {
		printf("│"); // 좌측 경계
		for (i = 0; i < num_fields; i++) {
			printf(" %-*s ", col_widths[i], row[i] ? row[i] : "NULL"); // 데이터 출력 (좌우 정렬)
			if (i < num_fields - 1) {
				printf("│"); // 열 사이 구분자
			}
		}
		printf("│\n"); // 우측 경계
	}

	set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // 파란색으로 설정
	printf("└"); // 좌측 경계
	for (i = 0; i < num_fields; i++) {
		for (int j = 0; j < col_widths[i] + 2; j++) {
			printf("─");
		}
		if (i < num_fields - 1) {
			printf("┴"); // 열 사이 구분자
		}
	}
	printf("┘\n"); // 테이블 하단 경계
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 기본 색상으로 설정

	free(col_widths); // 동적 할당 해제
}

int main(int argc, char** argv) {
	MYSQL* con = mysql_init(NULL); // MySQL 연결 객체 초기화

	if (con == NULL) {
		fprintf(stderr, "mysql_init() failed\n");
		exit(1);
	}

	// MySQL 연결 설정 (user, password, dbname은 실제 값으로 변경)
	if (mysql_real_connect(con, "localhost", "root", "tkfkdgody1#", "MyNewDatabase", 0, NULL, 0) == NULL) {
		finish_with_error(con); // 연결 실패 시 에러 처리
	}

	while (1) { // 메인 루프 시작
		int main_choice, sub_choice; // main_choice = 카테고리, sub_choice = 선택된 카테고리의 세부 항복
		print_category_menu(); // 카테고리 메뉴 출력
		scanf_s("%d", &main_choice, sizeof(main_choice)); // 사용자 입력 받기

		// 프로그램 종료
		if (main_choice == 0) {
			mysql_close(con); // MySQL 연결 종료
			exit(0);
		}

		switch (main_choice) {
		case 1: // 프로그래밍 언어 선택
			do { // do-while 루프로 변경 (최소 한 번 실행)
				print_language_menu(); // 프로그램 언어 메뉴 출력
				scanf_s("%d", &sub_choice, sizeof(sub_choice));  // 사용자 입력 받기

				if (sub_choice != 0) { // 0이 아닌 경우에만 실행 (뒤로 가기 선택 제외)
					char query_lang[256];  // SQL 쿼리 저장할 변수

					switch (sub_choice) {  // 선택된 언어에 따라 쿼리 생성
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
					case 0:  // 뒤로 가기 (루프 종료)
						mysql_close(con);
						exit(0);
					default:  // 잘못된 선택 처리
						printf("잘못된 선택입니다.\n");
						continue; // switch 문 처음으로 이동
					}

					if (mysql_query(con, query_lang)) {  // 쿼리 실행
						finish_with_error(con);  // 쿼리 실행 실패 시 에러 처리
					}

					MYSQL_RES* lang_result = mysql_store_result(con);  // 쿼리 결과 저장
					if (lang_result == NULL) {
						finish_with_error(con);  // 결과 저장 실패 시 에러 처리
					}

					// 결과 출력
					print_data(lang_result);  // 결과 출력 함수 호출
					mysql_free_result(lang_result);  // 결과 메모리 해제
				}
			} while (sub_choice != 0); // sub_choice가 0이면 루프 종료
			break;

		case 2: // IDE 선택
			do { // IDE 메뉴 루프 시작
				print_ide_menu();  // IDE 메뉴 출력
				scanf_s("%d", &sub_choice, sizeof(sub_choice));  // 사용자 입력 받기

				if (sub_choice != 0) { // 0이 아닌 경우에만 실행 (뒤로 가기 선택 제외)
					char query_ide[256];  // SQL 쿼리 저장할 변수

					switch (sub_choice) {  // 선택된 IDE에 따라 쿼리 생성
					case 1:
						snprintf(query_ide, sizeof(query_ide), "SELECT name, language, Description FROM IDE WHERE name = 'PyCharm'");
						break;
					case 2:
						snprintf(query_ide, sizeof(query_ide), "SELECT name, language, Description FROM IDE WHERE name = 'IntelliJ'");
						break;
					case 3:
						snprintf(query_ide, sizeof(query_ide), "SELECT name, language, Description FROM IDE WHERE name = 'GoLand'");
						break;
					case 4:
						snprintf(query_ide, sizeof(query_ide), "SELECT name, language, Description FROM IDE WHERE name = 'Rider'");
						break;
					case 5:
						snprintf(query_ide, sizeof(query_ide), "SELECT name, language, Description FROM IDE WHERE name = 'CLion'");
						break;
					case 6:
						snprintf(query_ide, sizeof(query_ide), "SELECT name, language, Description FROM IDE WHERE name = 'RustRover'");
						break;
					case 7:
						snprintf(query_ide, sizeof(query_ide), "SELECT name, language, Description FROM IDE WHERE name = 'WebStorm'");
						break;
					case 8:
						snprintf(query_ide, sizeof(query_ide), "SELECT name, language, Description FROM IDE WHERE name = 'RubyMine'");
						break;
					default:  // 잘못된 선택 처리
						printf("잘못된 선택입니다.\n");
						continue;  // switch 문 처음으로 이동
					}

					if (mysql_query(con, query_ide)) {  // 쿼리 실행
						finish_with_error(con);  // 쿼리 실행 실패 시 에러 처리
					}

					MYSQL_RES* ide_result = mysql_store_result(con);  // 쿼리 결과 저장
					if (ide_result == NULL) {
						finish_with_error(con);  // 결과 저장 실패 시 에러 처리
					}

					// 쿼리 결과 출력
					print_data(ide_result);  // 결과 출력 함수 호출
					mysql_free_result(ide_result);  // 결과 메모리 해제
				}

			} while (sub_choice != 0); // sub_choice가 0이면 루프 종료
			break;

		default: // 잘못된 선택 처리
			printf("잘못된 선택입니다.\n");
			break;
		} // switch (main_choice) 끝
	} // while (1) 끝

	return 0;
}
