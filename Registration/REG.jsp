

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page import ="java.sql.*" %>
<%@page language="java" %>
<%@page import="java.lang.String"%>


<% String acn = request.getParameter("accountnumber");
String cdn = request.getParameter("cardnumber");
    String cname = request.getParameter("cardholdername");
     String add = request.getParameter("address");
    String userid = request.getParameter("username");
    String pwd = request.getParameter("password");
    String phn = request.getParameter("phonenumber");
   
    out.println(acn);
    System.out.println(acn);
    %>
   <%=acn%>
    <%
    
    try{
    
    Class.forName("com.mysql.jdbc.Driver");
    
    Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/security","root","12345");
    Statement st = con.createStatement();
    ResultSet rs;
   st.executeUpdate("Insert into login(username,password) values ('" + userid + "','" + pwd + "')");
    st.executeUpdate("Insert into registration(accountnumber,cardnumber,cardholdername,address,phonenumber,username) values ('" +acn+"','" + cdn + "','" + cname +"','" + add + "','"+phn+"','" + userid + "')");
    
    }
    catch(Exception e)
    {out.println(e);
    }
    
   // if(rs.next()) {
     //  session.setAttribute("userid", userid);
       // out.println("login success");
        //response.sendRedirect("login.jsp");
   // }else{
     //   out.println("Invalid password try again");
  
     %>
    
    
