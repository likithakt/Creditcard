<%-- 
    Document   : otp
    Created on : 2 Feb, 2014, 10:58:26 AM
    Author     : dell
--%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page language="java" %>
<%@ page import ="smsproject.SendMessage" %>
<%
    String userid=session.getAttribute("userid").toString();
  
   try{ 
       SendMessage s=new SendMessage();
       s.doIt(userid);
   
   out.write("<script>alert('OTP sent to your registered mobile number')</script>"); 
   out.write("<script>window.location='otp.html'</script>");
   
     
   }catch(Exception e){out.println(e);}
     
   
            %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        
    </head>
    <body>
       
    </body>
</html>
