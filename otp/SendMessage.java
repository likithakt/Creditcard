package smsproject;
import org.smslib.AGateway;
import org.smslib.IOutboundMessageNotification;
import org.smslib.Library;
import org.smslib.OutboundMessage;
import org.smslib.Service;
import org.smslib.modem.SerialModemGateway;
import java.util.*;
import java.sql.*;


public class SendMessage
{
     String number;
    public void doIt(String userid) throws Exception
    {
      
        //OutboundNotification outboundNotification = new OutboundNotification();
        System.out.println("Example: Send message from a serial gsm modem.");
        System.out.println(Library.getLibraryDescription());
        System.out.println("Version: " + Library.getLibraryVersion());
        SerialModemGateway gateway = new SerialModemGateway("modem.com6", "COM6", 115200, "Huawei", "");
        gateway.setInbound(true);
        gateway.setOutbound(true);
        gateway.setSimPin("0000");
        // gateway.setSmscNumber("+919495513154");
        //Service.getInstance().setOutboundMessageNotification(outboundNotification);
        Service.getInstance().addGateway(gateway);
         
          
        Service.getInstance().startService();
        System.out.println();
       // System.out.println("GetGatewayId"+gateway.getGatewayId());
        System.out.println("Modem Information:");
        System.out.println("  Manufacturer: " + gateway.getManufacturer());
        System.out.println("  Model: " + gateway.getModel());
        System.out.println("  Serial No: " + gateway.getSerialNo());
        System.out.println("  SIM IMSI: " + gateway.getImsi());
        System.out.println("  Signal Level: " + gateway.getSignalLevel() + " dBm");
        System.out.println("  Battery Level: " + gateway.getBatteryLevel() + "%");
        System.out.println();
        // Send a message synchronously.
       
        Random rand= new Random();
        String rval=Integer.toString(rand.nextInt(10000));
        
      try{  
        Class.forName("com.mysql.jdbc.Driver");
    
    Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/security","root","root");
    Statement st = con.createStatement();
    ResultSet rs=null;
         
        rs= st.executeQuery("select * from registration where username='" + userid + "'");
        while(rs.next()){
         System.out.println( "the number is" + rs.getString(5));
       number = rs.getString(5);   
        }
        
    
        OutboundMessage msg = new OutboundMessage(number,rval);
        Service.getInstance().sendMessage(msg);
        System.out.println(msg);
        System.out.println("Now Sleeping - Hit <enter> to terminate.");
       //System.in.read();
       //System.in.read();
     
       Service.getInstance().stopService();
     
       st.executeUpdate("update login set otp='"+rval+"' where username='"+userid+"'");
    }
      catch(Exception e)
      {System.out.println(e);}
     
    }

    public static void main(String args[])
    {
        SendMessage app = new SendMessage();
        try
        {
            app.doIt(null);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
    
}
