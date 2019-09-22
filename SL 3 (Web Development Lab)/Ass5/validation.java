
import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
public class validation extends HttpServlet
{
public void doGet(HttpServletRequest req,HttpServletResponse res)throws ServletException,IOException
{
res.setContentType("text/html");
PrintWriter out=res.getWriter();
String str1=req.getParameter("t1");
String str2=req.getParameter("t2");
if(str1.equals("itexam") && str2.equals("Maywpu#18"))
{
out.println("VALID");
}
else
{
out.println("INVALID");
}
}
}