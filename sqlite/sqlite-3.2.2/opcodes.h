/* Automatically generated.  Do not edit */
/* See the mkopcodeh.awk script for details */
#define OP_MemMax                               1
#define OP_RowData                              2
#define OP_OpenTemp                             3
#define OP_AggInit                              4
#define OP_CreateIndex                          5
#define OP_Variable                             6
#define OP_MemStore                             7
#define OP_AggFunc                              8
#define OP_Clear                                9
#define OP_Last                                10
#define OP_Add                                 81   /* same as TK_PLUS     */
#define OP_MoveGe                              11
#define OP_SortNext                            12
#define OP_RowKey                              13
#define OP_Divide                              84   /* same as TK_SLASH    */
#define OP_SortInsert                          14
#define OP_ResetCount                          15
#define OP_Delete                              16
#define OP_SortReset                           17
#define OP_Rowid                               18
#define OP_OpenRead                            19
#define OP_Sort                                20
#define OP_VerifyCookie                        21
#define OP_Next                                22
#define OP_Insert                              23
#define OP_AggGet                              24
#define OP_ListReset                           25
#define OP_ListRead                            26
#define OP_Prev                                27
#define OP_IdxGE                               28
#define OP_Not                                 64   /* same as TK_NOT      */
#define OP_Ge                                  75   /* same as TK_GE       */
#define OP_DropTable                           29
#define OP_MakeRecord                          30
#define OP_Null                                31
#define OP_IdxIsNull                           32
#define OP_IdxInsert                           33
#define OP_ReadCookie                          34
#define OP_DropIndex                           35
#define OP_IsNull                              68   /* same as TK_ISNULL   */
#define OP_MustBeInt                           36
#define OP_Callback                            37
#define OP_IntegrityCk                         38
#define OP_MoveGt                              39
#define OP_MoveLe                              40
#define OP_CollSeq                             41
#define OP_HexBlob                            129   /* same as TK_BLOB     */
#define OP_Eq                                  71   /* same as TK_EQ       */
#define OP_String8                             90   /* same as TK_STRING   */
#define OP_Found                               42
#define OP_If                                  43
#define OP_Multiply                            83   /* same as TK_STAR     */
#define OP_Dup                                 44
#define OP_ShiftRight                          80   /* same as TK_RSHIFT   */
#define OP_Goto                                45
#define OP_Function                            46
#define OP_Pop                                 47
#define OP_Blob                                48
#define OP_MemIncr                             49
#define OP_BitNot                              89   /* same as TK_BITNOT   */
#define OP_IfMemPos                            50
#define OP_IdxGT                               51
#define OP_Gt                                  72   /* same as TK_GT       */
#define OP_Le                                  73   /* same as TK_LE       */
#define OP_AggFocus                            52
#define OP_NullRow                             53
#define OP_Transaction                         54
#define OP_IdxRowid                            55
#define OP_SetCookie                           56
#define OP_Negative                            87   /* same as TK_UMINUS   */
#define OP_And                                 63   /* same as TK_AND      */
#define OP_AggSet                              57
#define OP_ContextPush                         58
#define OP_DropTrigger                         59
#define OP_MoveLt                              60
#define OP_AutoCommit                          61
#define OP_Column                              65
#define OP_AbsValue                            66
#define OP_AddImm                              67
#define OP_Remainder                           85   /* same as TK_REM      */
#define OP_AggReset                            76
#define OP_ContextPop                          88
#define OP_IdxDelete                           91
#define OP_Ne                                  70   /* same as TK_NE       */
#define OP_Concat                              86   /* same as TK_CONCAT   */
#define OP_Return                              92
#define OP_Expire                              93
#define OP_Rewind                              94
#define OP_Statement                           95
#define OP_AggContextPush                      96
#define OP_BitOr                               78   /* same as TK_BITOR    */
#define OP_Integer                             97
#define OP_AggContextPop                       98
#define OP_Destroy                             99
#define OP_IdxLT                              100
#define OP_Lt                                  74   /* same as TK_LT       */
#define OP_Subtract                            82   /* same as TK_MINUS    */
#define OP_Vacuum                             101
#define OP_IfNot                              102
#define OP_Pull                               103
#define OP_ListRewind                         104
#define OP_ParseSchema                        105
#define OP_NewRowid                           106
#define OP_SetNumColumns                      107
#define OP_BitAnd                              77   /* same as TK_BITAND   */
#define OP_String                             108
#define OP_NotExists                          109
#define OP_Close                              110
#define OP_Halt                               111
#define OP_Noop                               112
#define OP_OpenPseudo                         113
#define OP_Or                                  62   /* same as TK_OR       */
#define OP_ShiftLeft                           79   /* same as TK_LSHIFT   */
#define OP_ListWrite                          114
#define OP_IsUnique                           115
#define OP_ForceInt                           116
#define OP_AggNext                            117
#define OP_OpenWrite                          118
#define OP_Gosub                              119
#define OP_Real                               128   /* same as TK_FLOAT    */
#define OP_Distinct                           120
#define OP_NotNull                             69   /* same as TK_NOTNULL  */
#define OP_MemLoad                            121
#define OP_NotFound                           122
#define OP_CreateTable                        123
#define OP_Push                               124

/* The following opcode values are never used */
#define OP_NotUsed_125                        125
#define OP_NotUsed_126                        126
#define OP_NotUsed_127                        127

#define NOPUSH_MASK_0 53146
#define NOPUSH_MASK_1 15099
#define NOPUSH_MASK_2 44987
#define NOPUSH_MASK_3 65406
#define NOPUSH_MASK_4 65529
#define NOPUSH_MASK_5 64447
#define NOPUSH_MASK_6 60405
#define NOPUSH_MASK_7 5631
#define NOPUSH_MASK_8 0
#define NOPUSH_MASK_9 0
