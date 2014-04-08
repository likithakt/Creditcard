<%-- 
    Document   : purchase
    Created on : 6 Feb, 2014, 4:40:23 PM
    Author     : CHIRAG
--%>


<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page language="java" %>
<%@page import ="jhmm.Match3"%>
<%
     String transamt = request.getParameter("s1");
    // out.write("Trans amt"+transamt);
   Match3 m = new Match3();
   try{  m.start_transaction(transamt);
   
   }catch(Exception e){out.println(e);}
   response.sendRedirect("otp.html");
    
    // SendMessage s=new SendMessage();
   // s.doIt();
            %>

<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        
    </head>
   
    <body>
        <h1>THANK U FOR BUYING OUR PRODUCT!</h1>
    </body>
</html>
