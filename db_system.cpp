#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<iostream>
#include <stdio.h>
#include<vector>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<map>
using namespace std;

typedef struct sinfo {
	int id;  // 1 <= id <= 1,000,000,000
	int grade; // 1 <= <= 3
	char gender[7]; // male / female
	int score; // 0 <= <= 300,000

	void set(int mId, int mGrade, char mGender[7], int mScore) {
		id = mId;
		grade = mGrade;
		strcpy(gender, mGender);
		score = mScore;
	}
};

typedef pair<int, sinfo> p;
typedef multimap<int, sinfo> mm;
typedef mm::iterator iter;

// key 오름차순 정렬
// key: score
mm main_data[3][2];
// key: id
mm st;

void init() {
	// 등록된 성적이 없는 상태
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			main_data[i][j].clear();
		}
	}

	st.clear();
}


int add(int mId, int mGrade, char mGender[7], int mScore) {
	// mGrade 학년 mGender인 학생 중에서 점수가 가장 높은 학생의 ID를 반환
	// 점수가 가장 놓은 학생의 id 리턴
	// 여러명일 땐 id 값이 가장 큰 거
	sinfo sitem;
	sitem.set(mId, mGrade, mGender, mScore);

	// key는 id
	st.insert(p(sitem.id, sitem));

	int gIdx = 0;
	if (strcmp(mGender, "female") == 0)
		gIdx = 1;

	// key는 score
	main_data[mGrade - 1][gIdx].insert(p(sitem.score, sitem));

	iter end = main_data[mGrade - 1][gIdx].end();
	end--;
	int maxScore = end->first;

	pair<iter, iter> pair_it = main_data[mGrade - 1][gIdx].equal_range(maxScore);

	int ret = 0;
	for (iter it = pair_it.first; it != pair_it.second; it++) {
		ret = max(ret, it->second.id);
	}
	cout << ret << endl;
	return ret;
}

int remove(int mId) {
	// 학생 ID가 학생의 기록 삭제
	// mId 학생의 점수가 기록되어 있지 않다면 0 반환
	// 삭제 후 mId 학생의 학년과 성별이 동일한 학생 중에서 점수가 가장 낮은 학생의 ID 반환
	// 삭제 후 아무것도 없다면 0

	// mId인 반환자 찾기
	iter it = st.find(mId);

	if (it == st.end()) {
		//없음
		cout << 0 << endl;
		return 0;
	}

	// 학년
	int grade = it->second.grade - 1;
	// 성별
	int gIdx = 0;
	// 점수
	int score = it->second.score;
	if (strcmp(it->second.gender, "female") == 0)
		gIdx = 1;

	//printf("remove node: %d %d %s %d\n", it->second.id, it->second.grade,
		//it->second.gender, it->second.score);

	// st에서 mId 를 key 로 가지는 원소 지우기
	st.erase(it);

	// key로 score를 갖는 main_data 원소 중
	pair<iter, iter> pair_it = main_data[grade][gIdx].equal_range(score);

	for (it = pair_it.first; it != pair_it.second; it++) {
		// mId와 같다면 삭제
		if (it->second.id == mId) {
			main_data[grade][gIdx].erase(it);
			break;
		}
	}

	if (main_data[grade][gIdx].size() == 0) {
		// 삭제 후 아무것도 없음
		cout << 0 << endl;
		return 0;
	}

	int ret = 1000000001;
	// 최소 key값을 갖는 반환자
	iter start = main_data[grade][gIdx].begin();
	int minScore = start->first;

	// 최소 score를 갖는 원소들 중
	pair_it = main_data[grade][gIdx].equal_range(minScore);

	// id 값이 가장 작은
	for (iter it = pair_it.first; it != pair_it.second; it++) {
		//printf("%d %d %s %d\n", it->second.id, it->second.grade,
			//it->second.gender, it->second.score);
		ret = min(ret, it->second.id);
	}

	cout << ret << endl;
	return ret;
}

void print();

void get_min(int mGrade, char mGender[7], int mScore, int* ret_score, int* ret_id) {
	int gIdx = 0;
	if (strcmp(mGender, "female") == 0)
		gIdx = 1;

	if (main_data[mGrade - 1][gIdx].size() == 0) {
		return;
	}

	iter end = main_data[mGrade - 1][gIdx].end();
	end--;
	int maxScore = end->first;

	if (maxScore < mScore) {
		return;
	}

	int upper_score = mScore;
	iter find_it = main_data[mGrade - 1][gIdx].find(mScore);
	if (find_it == main_data[mGrade - 1][gIdx].end()) {
		iter upper_it = main_data[mGrade - 1][gIdx].upper_bound(mScore);
		upper_score = upper_it->first;
	}

	pair<iter, iter> pair_it = main_data[mGrade - 1][gIdx].equal_range(upper_score);

	(*ret_score) = upper_score;

	int temp_id = 1000000001;


	for (iter it = pair_it.first; it != pair_it.second; it++) {
		temp_id = min(temp_id, it->second.id);
	}

	(*ret_id) = temp_id;
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
	// mGrade 학년 집합과 mGender 성별 집합에 속하면서, 점수가 mScroe 이상인 학생 중에서
	// 점수가 가장 낮은 학생의 ID를 반환(여러 개면 ID 가장 작은 값)
	// 없다면 0 반환

	// 0, 1, 2
	// 0, 1
	int ret = 0;
	int score = 0;
	int id = 0;
	int min_score = 300000;

	for (int i = 0; i < mGradeCnt; i++) {
		for (int j = 0; j < mGenderCnt; j++) {

			score = 0;
			id = 0;

			get_min(mGrade[i], mGender[j], mScore, &score, &id);

			//printf("score, id: %d %d\n", score, id);

			if (score == 0)
				continue;

			if (min_score > score) {
				min_score = score;
				ret = id;
			}
			else if (min_score == score) {
				if (ret > id)
					ret = id;
			}
			//printf("new ret: %d\n", ret);

		}
	}

	cout << ret << endl;
	return ret;
}

void print() {
	for (int i = 0; i < 3; i++) {
		cout << "-------------------- " << i + 1 << "학년 ----------------------" << endl;
		for (int j = 0; j < 2; j++) {
			cout << "------- " << j << "-------" << endl;
			for (iter it = main_data[i][j].begin(); it != main_data[i][j].end(); it++) {
				printf("%d %d %s %d\n", it->second.id, it->second.grade,
					it->second.gender, it->second.score);
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////

#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_REMOVE 300
#define CMD_QUERY 400
#define CMD_PRINT 500

static bool run() {
	int q;  // query 개수
	scanf("%d", &q);

	int id, grade, score;
	char gender[7];
	int cmd, ans, ret;
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		if (i > 0 && !okay) {
			break;
		}
		switch (cmd) {
		case CMD_INIT:   // cmd == 100
			init();
			okay = true;
			break;
		case CMD_ADD:  // cmd == 200
			// 추가할 학생의
			// id, grade, gender, score, ans
			// ans는 제공된 정답
			scanf("%d %d %s %d %d", &id, &grade, gender, &score, &ans);
			// ret = grade, gender 중에서 점수가 가장 높은 학생의 id 
			ret = add(id, grade, gender, score);
			if (ans != ret)
				okay = false;
			break;
		case CMD_REMOVE:  // cmd == 300
			scanf("%d %d", &id, &ans);
			ret = remove(id);
			if (ans != ret)
				okay = false;
			break;
		case CMD_QUERY: {  // cmd == 400
			int gradeCnt, genderCnt;
			int gradeArr[3];
			char genderArr[2][7];
			scanf("%d", &gradeCnt);
			if (gradeCnt == 1) {
				scanf("%d %d", &gradeArr[0], &genderCnt);
			}
			else if (gradeCnt == 2) {
				scanf("%d %d %d", &gradeArr[0], &gradeArr[1], &genderCnt);
			}
			else {
				scanf("%d %d %d %d", &gradeArr[0], &gradeArr[1], &gradeArr[2], &genderCnt);
			}

			if (genderCnt == 1) {
				scanf("%s %d %d", genderArr[0], &score, &ans);
			}
			else {
				scanf("%s %s %d %d", genderArr[0], genderArr[1], &score, &ans);
			}
			ret = query(gradeCnt, gradeArr, genderCnt, genderArr, score);
			if (ans != ret)
				okay = false;
			break;
		}
		case CMD_PRINT: {
			print();
			break;
		}
		default:
			okay = false;
			break;
		}
	}
	return okay;
}

int main() {
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	// 테스트 케이스 성공 ? MARK : 0
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}