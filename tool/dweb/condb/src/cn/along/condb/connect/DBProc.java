package cn.along.condb.connect;

import java.sql.Connection;
import java.util.Map;

import cn.along.condb.exception.DBException;

public class DBProc
{
    private Connection conn;

    public DBProc(Connection conn)
    {
        this.conn = conn;
    }

    public <T> void callProc(String sql, T object, Map<String, Object> param)
            throws DBException
    {
        throw new DBException("unsupport");
    }
}
