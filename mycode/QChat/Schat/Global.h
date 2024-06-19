#ifndef GLOBAL_H
#define GLOBAL_H
#include<functional>
#include<QWidget>
#include"QStyle"
/**
 * @brief repolish 用来刷新QSS
 */
extern std::function<void (QWidget*)> repolish;
#endif // GLOBAL_H
