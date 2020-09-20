Action()
{
	lr_start_transaction("04_itinerary");
		
		lr_start_transaction("Load_start_Page");
	
		web_reg_save_param_ex(
			"ParamName=userSession",
			"LB=name=\"userSession\" value=\"",
			"RB=\"/>",
			"Ordinal=1",
				SEARCH_FILTERS,
			LAST);	

		//ѕроверка соответсви€ на корректности загрузки страницы
		web_reg_find("Text=Welcome to the Web Tours site", LAST);
		
		web_url("WebTours",
			"URL=http://localhost:1080/WebTours/", 
			"TargetFrame=", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=", 
			"Snapshot=t1.inf", 
			"Mode=HTML", 
			LAST);		
		lr_end_transaction("Load_start_Page", LR_AUTO);

		//SLA секунд ожидание действий пользовател€
		lr_think_time(5);	
				
		lr_start_transaction("login_user");
			//ѕроверка соответсви€ на корректности загрузки страницы
			web_reg_find("Text=User password was correct", LAST);
			
			web_submit_data("login.pl",
				"Action=http://localhost:1080/cgi-bin/login.pl",
				"Method=POST",
				"TargetFrame=body",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
				"Snapshot=t2.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=userSession", "Value={userSession}", ENDITEM,
				"Name=username", "Value={User_Login}", ENDITEM,
				"Name=password", "Value={User_Pass}", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				"Name=login.x", "Value=60", ENDITEM,
				"Name=login.y", "Value=9", ENDITEM,
				LAST);		
		lr_end_transaction("login_user",LR_AUTO);
	
		//SLA секунд ожидание действий пользовател€
		lr_think_time(5);
		
		lr_start_transaction("goto_Itinerary");
	
			//ѕроверка соответсви€ на корректности загрузки страницы
			web_reg_find("Text=Flights List",
			LAST);
			
			web_url("Itinerary Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("goto_Itinerary",LR_AUTO);
		
		//SLA секунд ожидание действий пользовател€
		lr_think_time(5);
		lr_think_time(67);
		
		lr_start_transaction("Logout");
		
			//ѕроверка соответсви€ на корректности загрузки страницы
			web_reg_find("Text=To make reservations,please enter your account information to the left.",
				LAST);
			web_url("welcome.pl",
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t9.inf", 
				"Mode=HTML", 
				LAST);
		lr_end_transaction("Logout", LR_AUTO);
				
	lr_end_transaction("04_itinerary", LR_AUTO);

	return 0;
}
