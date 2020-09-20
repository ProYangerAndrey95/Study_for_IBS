Action()
{
	//int pass_count = 0;

	lr_start_transaction("02_Search_BuyTicket");
		
		lr_start_transaction("Load_start_Page");
	
			web_reg_save_param_ex(
				"ParamName=userSession",
				"LB=name=\"userSession\" value=\"",
				"RB=\"/>",
				"Ordinal=1",
					SEARCH_FILTERS,
				LAST);			
			
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
					
		lr_think_time(5);	
		
		lr_start_transaction("login_user");	
			
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
				
		//lr_think_time(5);
				
		lr_start_transaction("goto_Flight");		
			
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
			
		//lr_think_time(5);
	
		lr_start_transaction("Entry_Data_Flight");	
			
			web_reg_find("Text=Flight departing from <B>{depart}</B> to <B>{arrive}</B>",
				LAST);
			if (lr_eval_string("{roundtrip}")=="on"){
				web_reg_find("Text=Flight departing from <B>{arrive}</B> to <B>{depart}</B>",
					LAST);
		    }
			
			/*Correlation comment - Do not change!  Original value='202;600;07/16/2020' Name ='outboundFlight' Type ='ResponseBased'*/
//			web_reg_save_param_attrib(
//				"ParamName=outboundFlight",
//				"TagName=input",
//				"Extract=value",
//				"Name=outboundFlight",
//				"Type=radio",
//				SEARCH_FILTERS,
//				"IgnoreRedirections=No",
//				LAST);
			
			web_reg_save_param_ex(
				"ParamName=outboundFlight",
				"LB=name=\"outboundFlight\" value=\"",
				"RB=\"",
				SEARCH_FILTERS,
				LAST);			
			
//			/*Correlation comment - Do not change!  Original value='022;600;09/17/2020' Name ='returnFlight' Type ='ResponseBased'*/
//			web_reg_save_param_attrib(
//				"ParamName=returnFlight",
//				"TagName=input",
//				"Extract=value",
//				"Name=returnFlight",
//				"Type=radio",
//				SEARCH_FILTERS,
//				"IgnoreRedirections=No",
//				LAST);
			
			web_reg_save_param_ex(
				"ParamName=returnFlight",
				"LB=name=\"returnFlight\" value=\"",
				"RB=\"",
				SEARCH_FILTERS,
				LAST);	
			
			web_submit_data("reservations.pl",
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
				"Snapshot=t4.inf", 
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
				"Name=findFlights.x", "Value=58", ENDITEM, 
				"Name=findFlights.y", "Value=9", ENDITEM, 
				LAST);	
		lr_end_transaction("Entry_Data_Flight",LR_AUTO);
				
		//lr_think_time(5);
	
		lr_start_transaction("choise_ticket");	
			
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
		
		
		//lr_think_time(5);
	
		lr_start_transaction("Entry_Data_Ticket");
			
			web_reg_find("Search=Body",
				"Text=Thank you for booking through Web Tours.",
				LAST);
			web_reg_find("Search=Body",
				"Text=from {depart} to {arrive}.",
				LAST);				
		
			web_submit_data("reservations.pl_3",
				"Action=http://localhost:1080/cgi-bin/reservations.pl",
				"Method=POST",
				"TargetFrame=",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/reservations.pl",
				"Snapshot=t6.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=firstName", "Value={User_Name}", ENDITEM,
				"Name=lastName", "Value={User_FirstName}", ENDITEM,
				"Name=address1", "Value={User_Street}", ENDITEM,
				"Name=address2", "Value={User_Sity}", ENDITEM,
				"Name=pass1", "Value={Pass_FirstName} {Pass_Name}", ENDITEM,
				"Name=creditCard", "Value={CreditCard_Num}", ENDITEM,
				"Name=expDate", "Value={CreditCard_Val}", ENDITEM,
				"Name=oldCCOption", "Value=on", ENDITEM,
				"Name=numPassengers", "Value={numPassengers}", ENDITEM,
				"Name=seatType", "Value={seatType}", ENDITEM,
				"Name=seatPref", "Value={seatPref}", ENDITEM,
				//"Name=outboundFlight", "Value={out}", ENDITEM,
				"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
				"Name=advanceDiscount", "Value=0", ENDITEM,
				"Name=returnFlight", "Value={returnFlight}", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				"Name=.cgifields", "Value=saveCC", ENDITEM,
				"Name=buyFlights.x", "Value=41", ENDITEM,
				"Name=buyFlights.y", "Value=8", ENDITEM,
				LAST);	
		lr_end_transaction("Entry_Data_Ticket",LR_AUTO);
		
		
		lr_think_time(5);
		
		// выстав€ю расчетный ThinkTime
		lr_think_time(3);
	
		lr_start_transaction("goto_home");	
			
			web_reg_find("Text=Welcome, <b>{User_Login}</b>, to the Web Tours reservation pages.",
				LAST);
			
			web_url("welcome.pl", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t7.inf", 
				"Mode=HTML", 
				LAST);		
		lr_end_transaction("goto_home",LR_AUTO);
		
				
		lr_start_transaction("Logout");
		
			
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
		
	
	lr_end_transaction("02_Search_BuyTicket", LR_AUTO);


	return 0;
}
