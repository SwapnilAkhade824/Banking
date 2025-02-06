#include "../include/menus.h"
#include "../include/pages.h"
#include "../include/Admin.h"
#include <stdio.h>

int main() {

	
	long long accno = login_page_code();
	deposit_withdraw_check(accno);
    return 0;
}
