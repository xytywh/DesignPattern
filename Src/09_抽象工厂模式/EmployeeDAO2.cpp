//数据库访问有关的基类
class IDBConnection {
};

class IDBConnectionFactory {
public:
    virtual IDBConnection *CreateDBConnection() = 0;
};

class IDBCommand {
};

class IDBCommandFactory {
public:
    virtual IDBCommand *CreateDBCommand() = 0;
};

class IDataReader {
};

class IDataReaderFactory {
public:
    virtual IDataReader *CreateDataReader() = 0;
};

//支持SQL Server
class SqlConnection : public IDBConnection {
};

class SqlConnectionFactory : public IDBConnectionFactory {
};

class SqlCommand : public IDBCommand {
};

class SqlCommandFactory : public IDBCommandFactory {
};

class SqlDataReader : public IDataReader {
};

class SqlDataReaderFactory : public IDataReaderFactory {
};

//支持Oracle
class OracleConnection : public IDBConnection {
};

class OracleCommand : public IDBCommand {
};

class OracleDataReader : public IDataReader {
};

class EmployeeDAO {
    // 这几个对象指针之间其实有的是有相互关联的   但是如果按照下面的写法在传递的时候并不能保证这种约束 因此可能会出现问题
    IDBConnectionFactory *dbConnectionFactory;
    IDBCommandFactory *dbCommandFactory;
    IDataReaderFactory *dataReaderFactory;

public:
    vector <EmployeeDO> GetEmployees() {
        IDBConnection *connection = dbConnectionFactory->CreateDBConnection();
        connection->ConnectionString("...");

        IDBCommand *command = dbCommandFactory->CreateDBCommand();
        command->CommandText("...");
        command->SetConnection(connection); //关联性

        IDBDataReader *reader = command->ExecuteReader(); //关联性
        while (reader->Read()) {
        }
    }
};
