Action()
{

	lr_start_transaction("01_Search_Itinerary");
	
		lr_start_transaction("Load_start_Page");			
	
			web_reg_save_param_ex(
				"ParamName=userSession",
				"LB=name=\"userSession\" value=\"",
				"RB=\"/>",
				"Ordinal=1",
					SEARCH_FILTERS,
				LAST);	
		
			//ѕроверка соответсви€ на корректность загрузки страницы
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

		//ожидание от пользовател€ ввода login pass	
		lr_think_time(5);			
		
		lr_start_transaction("login_user");		
		
			//ѕроверка соответсви€ на корректность загрузки страницы
			web_reg_find("Text=Welcome, <b>{User_Login}</b>, to the Web Tours reservation pages.", LAST);

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
		
		//SLA 5 секунд ожидание действи€ пользовател€
		lr_think_time(5);					
		
		lr_start_transaction("goto_Flight");	

			//ѕроверка соответсви€ на корректность загрузки страницы
			web_reg_find("Text=Find Flight",
			LAST);	
			
			web_url("welcome.pl", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t12.inf", 
				"Mode=HTML", 
				LAST);
		lr_end_transaction("goto_Flight",LR_AUTO);
	
		//SLA 26 секунд на ввод всех данных в форму на странице
		//lr_think_time(5);
	
		lr_start_transaction("Entry_Data_Flight");		
			//ѕроверка соответсви€ на корректность загрузки страницы
			web_reg_find("Text=Flight departing from <B>{depart}</B> to <B>{arrive}</B>",
				LAST);
			if (lr_eval_string("{roundtrip}")=="on"){
				web_reg_find("Text=Flight departing from <B>{arrive}</B> to <B>{depart}</B>",
					LAST);
		    }	
						
			web_submit_data("reservations.pl", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
				"Snapshot=t13.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=depart", "Value={depart}", ENDITEM, 
				"Name=departDate", "Value={departDate}", ENDITEM, 
				"Name=arrive", "Value={arrive}", ENDITEM, 
				"Name=returnDate", "Value={returnDate}", ENDITEM, 
				"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
				"Name=roundtrip", "Value={roundtrip}", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=.cgifields", "Value=roundtrip", ENDITEM, 
				"Name=.cgifields", "Value=seatType", ENDITEM, 
				"Name=.cgifields", "Value=seatPref", ENDITEM, 
				"Name=findFlights.x", "Value=52", ENDITEM, 
				"Name=findFlights.y", "Value=10", ENDITEM, 
				LAST);			
		lr_end_transaction("Entry_Data_Flight",LR_AUTO);
	
		//SLA 15 секунд ожидание действий пользовател€
		//lr_think_time(5);
		
		// подгонка под значени€ из домашнего задани€
		lr_start_transaction("choise_ticket");	
			//ѕроверка соответсви€ на корректность загрузки страницы
			web_reg_find("Search=Body",
				"Text=Flight Reservation",
				LAST);	
			web_reg_find("Search=Body",
				"Text={User_Name}",
				LAST);
			web_reg_find("Search=Body",
				"Text={User_FirstName}",
				LAST);			
						
			web_submit_data("reservations.pl_2",
				"Action=http://localhost:1080/cgi-bin/reservations.pl",
				"Method=POST",
				"TargetFrame=",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/reservations.pl",
				"Snapshot=t5.inf",
				"Mode=HTML",
				ITEMDATA,
				//"Name=outboundFlight", "Value={out}", ENDITEM, 
				"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
				"Name=returnFlight", "Value={returnFlight}", ENDITEM,
				"Name=numPassengers", "Value={numPassengers}", ENDITEM,
				"Name=advanceDiscount", "Value=0", ENDITEM,
				"Name=seatType", "Value={seatType}", ENDITEM,
				"Name=seatPref", "Value={seatPref}", ENDITEM,
				"Name=reserveFlights.x", "Value=60", ENDITEM,
				"Name=reserveFlights.y", "Value=8", ENDITEM,
				LAST);	
		lr_end_transaction("choise_ticket",LR_AUTO);
		
		//SLA 15 секунд ожидание действий пользовател€
		//lr_think_time(5);
		
		lr_start_transaction("goto_Itinerary");	

			//ѕроверка соответсви€ на корректность загрузки страницы
			web_reg_find("Fail=Found",
				"Text=No flights have been reserved",
				"SaveCount=erroMess",
				LAST);
						
			web_reg_save_param_ex(
				"ParamName=flightId",
				"LB=name=\"flightID\" value=\"",
				"RB=\"  />",
				"Ordinal=ALL",
					SEARCH_FILTERS,
				LAST);		
			
			web_url("Itinerary Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);			
						
		lr_end_transaction("goto_Itinerary", LR_AUTO);
		
		//SLA 5 секунд ожидание действий пользовател€
		//lr_think_time(5);
		
		lr_start_transaction("goto_home");
			//ѕроверка соответсви€ на корректность загрузки страницы
			web_reg_find("Text=Welcome, <b>{User_Login}</b>, to the Web Tours reservation pages.",
				LAST);
			
			web_url("welcome.pl", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t16.inf", 
				"Mode=HTML", 
				LAST);	
		lr_end_transaction("goto_home",LR_AUTO);
		
		//SLA 5 секунд ожидание действий пользовател€
		// выстав€ю расчетный ThinkTime
		lr_think_time(20);
	
		lr_start_transaction("Logout");
			//ѕроверка соответсви€ на корректность загрузки страницы
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
	
	lr_end_transaction("01_Search_Itinerary", LR_AUTO);


	return 0;
}