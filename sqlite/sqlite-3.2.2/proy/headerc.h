#ifdef __cplusplus
extern "C" {
#endif
	int init_sqlite(void);
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
#ifdef __cplusplus
}
# endif
