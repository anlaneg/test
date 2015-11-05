package demo04;  
  
import java.sql.Connection;  
import java.sql.DriverManager;  
import java.sql.PreparedStatement;  
import java.sql.ResultSet;  
import java.util.Iterator;  
import java.util.List;  
  
import org.apache.commons.beanutils.DynaBean;  
import org.apache.commons.beanutils.ResultSetDynaClass;  
import org.apache.commons.beanutils.RowSetDynaClass;  
  
/** 
 * ResultSetDynaClass类可以包装java.sql.ResultSet类：一次返回一个结果 
 * RowSetDnyaClass类包装java.sql.ResultSet：一次性返回所以结果 
 */  
public class ResultSetDynaClassTest {  
  
    public static void main(String args[]) throws Exception {  
        readDBResult();  
    }  
  
    public static void readDBResult() throws Exception {  
        Connection conn = null;  
        ResultSet rs = null;  
        PreparedStatement pstmt = null;  
  
        try {  
            Class.forName("com.mysql.jdbc.Driver");  
            String url = "jdbc:mysql://localhost:3306/study?useUnicode=true&characterEncoding=GBK";  
            String username="root";  
            String password = "root";  
            conn = DriverManager.getConnection(url,username, password);  
            pstmt = conn.prepareStatement("select id,username, password from user");  
            rs = pstmt.executeQuery();  
              
            //使用java.sql.ResultSet输出  
            while(rs.next()) {  
                System.out.println("username=" + rs.getString("username"));  
            }  
              
            //使用Common BeanUtils中的ResultSetDynaClass类包装  
            System.out.println("-----------分割线---------------------");  
            rs.beforeFirst();//这里必须使用beforeFirst  
            ResultSetDynaClass rsdc = new ResultSetDynaClass(rs);  
            Iterator<DynaBean> rows = rsdc.iterator();  
            while(rows.hasNext()) {  
                DynaBean row = rows.next();  
                System.out.println("id=" + row.get("id") + ",username="   
                        + row.get("username") + ",password="  
                        + row.get("password"));  
            }  
              
            //使用RowSetDnyaClass类  
            System.out.println("-----------分割线---------------------");  
            rs.beforeFirst();//这里必须使用beforeFirst  
            RowSetDynaClass rc = new RowSetDynaClass(rs);  
            List<DynaBean> resultList = rc.getRows();  
            for(DynaBean db : resultList) {  
                System.out.print(db.get("id") + "\t");  
                System.out.print(db.get("username") + "\t");  
                System.out.println(db.get("password"));  
            }  
        } finally {  
            if(pstmt!=null)  
                pstmt.close();  
            if(rs!=null)  
                rs.close();  
            if(conn!=null)  
                conn.clearWarnings();  
        }  
    }  
} 