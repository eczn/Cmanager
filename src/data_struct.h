
struct subject_unit {
	char Sub_name[32];
	float credit;					/* 36 bytes */
	struct SubjectUnit *next; 
	struct user_score *us;
};

struct user_score {
	float score; 
	float BD_GPA;			// 单科成绩的绩点。 Billing Division GPA ( google translate	
};

