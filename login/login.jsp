 <%-- 
    Document   : login
    Created on : 21 Sep, 2013, 2:17:31 PM
    Author     : dell
--%>


<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page import ="java.sql.*" %>
<%@page language="java" %>
<%@ page import ="smsproject.SendMessage" %>


<%
    String userid = request.getParameter("username");
    String pwd = request.getParameter("password");
    //String userotp= request.getParameter("otp");
    out.println(userid+pwd);
    Class.forName("com.mysql.jdbc.Driver");
    
    Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/security","root","root");
    Statement st = con.createStatement();
    ResultSet rs;
    rs = st.executeQuery("select * from login where username='" + userid + "' and password='" + pwd + " '");
   
    if(rs.next()) {
        session.setAttribute("userid", userid);
        out.println("login success");
       response.sendRedirect("purchase.html");
       //session.setAttribute("userotp",userotp);
    }else{
        out.println("Invalid password try again");
    }
     %>
    
    
