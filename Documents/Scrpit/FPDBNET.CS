using System;
using System.Configuration;
using System.Collections;
using System.Collections.Specialized;
using System.Data;
using System.Data.OleDb;
using System.Globalization;
using System.Text;
using System.Web;
using System.Web.Caching;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;

namespace Microsoft.Office.FrontPage.DBInterface 
{
    /* This class implements the basic functionality of connecting to a database, providing DataSets 
     * and DataViews on the connection, and managing the cached version of the DataSet.
     */
    public class DBConnection
    {
        private OleDbConnection _dBConn = null;
        private OleDbDataAdapter _dataAdpater = null;
        private HttpServerUtility _server = null;
        private Page fpPage = null;
        private Cache _cache;
        private int _maxRecordCount;
        private string _cacheKey;
        private string _dBName;
        private string _tableName;
        private string _tableKey;
        private string _rootPath;
        private string _searchQuery;
        private ArrayList _paramList;

        public string CacheName         
        {
            get{
                if(_cacheKey == null)
                    _cacheKey = DBName;
                return _cacheKey;
            }
            set{
                _cacheKey = value;
            }
        }
                
        public string DBName
        {
            get{
                if(_dBName == null)
                    _dBName = ConfigurationSettings.AppSettings["DBName"];
                return _dBName;
            }
            set{
                _dBName = value;
            }
        }

        public int MaxRecordCount
        {
            get{
                return _maxRecordCount;
            }
            set{
                _maxRecordCount = value;
            }
        }

        public string RootPath
        {
            get{
                if(_rootPath == null)
                    _rootPath = ConfigurationSettings.AppSettings["RootPath"];
                return _rootPath;
            }
            set{
                _rootPath = value;
            }
        }

        public string SearchQuery
        {
            get{
                if(_searchQuery == null)
                    BuildSearchQuery();
                return _searchQuery;
            }
            set{
                _searchQuery = value;
            }
        }
        
        public string TableName
        {
            get{
                if(_tableName == null )
                    _tableName = ConfigurationSettings.AppSettings["TableName"];
                if(_tableName == null || _tableName.Length == 0)
                    _tableName = "Table";
                return _tableName;
            }
            set{
                _tableName = value;
            }
        }

        public string TableKey
        {
            get{
                if(_tableKey == null)
                    _tableKey = ConfigurationSettings.AppSettings["TableKey"];
                if(_tableKey == null || _tableKey.Length == 0)
                    SetTableKeyFromDataSet();
                return _tableKey;
            }
            set{
                _tableKey = value;
            }
        }

        
        
        public DBConnection(Page parentPage)
        {
            CacheName = "WorkingDataSet";
            fpPage = parentPage;
        }

    
        private HttpServerUtility GetServer()
        {
            if(_server == null)
            {
                _server = fpPage.Server;
            }

            return _server;
        }
                
        private Cache GetCache()
        {
            if(_cache == null)
            {
                _cache = fpPage.Cache;
            }        
            return _cache;
        }

        

        public virtual DataSet GetDataSet(bool useCache)
        {
            if(useCache && HasCache())
            {
                return (DataSet)GetCache()[CacheName];
            }
            else
            {
                DataSet theDataSet = new DataSet();
                theDataSet.Locale = CultureInfo.InvariantCulture;

                if(_dataAdpater == null)
                    GetConnection();

                ApplyParameters();
                if(MaxRecordCount > 0)
                {
                    _dataAdpater.Fill(theDataSet, 0, MaxRecordCount, TableName);
                }
                else
                {
                    _dataAdpater.Fill( theDataSet );
                }

                if(useCache)
                    GetCache()[CacheName] = theDataSet;

                return theDataSet;
            }
        }

        private void SetTableKeyFromDataSet()
        {
            if( TableKey == null )
            {
                TableKey = GetDataSet(true).Tables[0].Columns[0].ColumnName;
            }
        }

        public void RefreshCache()
        {
            GetCache()[CacheName] = GetDataSet(false);
        }

        public bool HasCache()
        {
            return (GetCache()[CacheName] != null && GetCache()[CacheName] is DataSet);
        }

        public DataView GetDataView( )
        {
            return GetDataSet( true ).Tables[0].DefaultView;
        }

        public DataView GetDataView( string rowFilter, string sortFilter )
        {
            return new DataView( GetDataSet( true ).Tables[ 0 ], rowFilter, sortFilter, DataViewRowState.Unchanged );
        }

        public virtual bool SaveChangesToDatabase()
        {
            if(_dataAdpater == null)
                GetConnection();

            try{
                _dataAdpater.Update(GetDataSet(true));
            }
            catch( System.Exception ex){
                throw new ApplicationException(ex.Message);
            }
            return true;
        }

        protected void BuildSearchQuery()
        {
            StringBuilder sb = new StringBuilder("SELECT * FROM ");
 
            sb.Append("[");
            sb.Append(TableName);
            sb.Append("]");

            SearchQuery = sb.ToString();
        }

        protected virtual void GetConnection()
        {
            if( DBName == null )
                throw new ApplicationException( "<%IDS_DBREGION_ASPNET_ERROR_NO_CONN_NAME%>" );

            String strProvider = ConfigurationSettings.AppSettings[ DBName + "_Provider" ];
            String strDataSource;
            String strDatabase = null;
            String strUsername = ConfigurationSettings.AppSettings[ DBName + "_RuntimeUsername" ];
            String strPassword = ConfigurationSettings.AppSettings[ DBName + "_RuntimePassword" ];
            String strAddition = ConfigurationSettings.AppSettings[ DBName + "_AdditionalParams" ];

            if(strProvider == null)
                throw new 
                    ApplicationException( "<%IDS_DBREGION_ASPNET_ERROR_NO_CONN_INFO%>");
            
            if(strProvider.Equals("Microsoft.Jet.OLEDB.4.0"))
            {
                strDataSource = GetServer().MapPath( RootPath + ConfigurationSettings.AppSettings[DBName + "_DataSource"] );
            }
            else
            {
                strDataSource = ConfigurationSettings.AppSettings[DBName + "_DataSource"];
                strDatabase = ConfigurationSettings.AppSettings[DBName + "_Database"];
            }

            StringBuilder strConString = new StringBuilder("Provider=");
            strConString.Append( strProvider );
            strConString.Append( ";Data Source=" );
            strConString.Append( strDataSource );
            if( strDatabase != null && strDatabase.Length != 0 )
               {
                strConString.Append("; Database=" );
                strConString.Append( strDatabase);
                }
            if( strUsername != null && strUsername.Length != 0 )
               {
                strConString.Append(  "; User ID=" );
                strConString.Append( strUsername);
                }
            if( strPassword != null && strPassword.Length != 0 )
               {
                strConString.Append( "; Password=" ); 
                strConString.Append( strPassword ); 
                }
            if( strAddition != null && strAddition.Length != 0 )
               { 
                strConString.Append( "; " );
                strConString.Append( strAddition );
               }

            _dBConn = new OleDbConnection(strConString.ToString());
            _dataAdpater = new OleDbDataAdapter(SearchQuery, _dBConn);
            OleDbCommandBuilder OdcbCommand = new OleDbCommandBuilder(_dataAdpater);

            try{
                _dBConn.Open();
                DataTable literalInfo = _dBConn.GetOleDbSchemaTable(OleDbSchemaGuid.DbInfoLiterals, null);
                OdcbCommand.QuotePrefix = (String)literalInfo.Select("LiteralName='Quote_Prefix'")[0]["LiteralValue"];
                OdcbCommand.QuoteSuffix = (String)literalInfo.Select("LiteralName='Quote_Suffix'")[0]["LiteralValue"];
            }
            catch( OleDbException ex ){
                throw new ApplicationException( "<%IDS_DBREGION_ASPNET_ERROR_CONN_FAILED%>", ex );
            }
            finally{
                _dBConn.Close();
            }
        }

       
        public void SetConnectionParameters(ArrayList parameterList)
        {
            _paramList = parameterList;
        }

        protected void ApplyParameters()
        {
            if(_paramList == null)
                return;
            if(_dataAdpater == null)
                return;
            OleDbParameterCollection CommandParams = _dataAdpater.SelectCommand.Parameters;
            CommandParams.Clear();
            int i;
            for(i=0;i<_paramList.Count;i++)
            {
                CommandParams.Add(new OleDbParameter("@P"+i, _paramList[i]));
            }
        }
    }

    /* This class provides a basic level of interaction between a page designed to work against a database
                                                             * and the database itself.  It has the ability to read data from controls found in the page and place them
                                                             * in a DataRow for insertion into the database.
                                                             */
    public abstract class DBInterfacePage : System.Web.UI.Page
    {
        private DBConnection _connection;
        private System.Web.UI.WebControls.Label _pageErrorLabel;
        private DBRegionBase _dBRegion;

        private StringCollection _fieldDefaultsCollection;
        private StringCollection _fieldFriendlyNamesCollection;
        private StringCollection _fieldNamesCollection;
        private StringCollection _fieldTypesCollection;
        private bool DebugOn = false;
        private string DefaultFieldValues;
        private string FriendlyNamesOfFields;
        private string NamesOfFields;
        private string TypesOfFields;

        public DBConnection Connection
        {
            get{
                return _connection;
            }
        }

        public DBRegionBase DBRegion
        {
            get{
                return _dBRegion;
            }
            set{
                _dBRegion = value;
            }
        }    
        public string FieldDefaults
        {
            get{                
                return DefaultFieldValues;
            }
            set{
                DefaultFieldValues = value;
            }
        }
        public string FieldNames
        {
            get{
                return NamesOfFields;
            }
            set{
                NamesOfFields = value;
            }
        }

        public string FieldFriendlyNames
        {
            get{
                return FriendlyNamesOfFields;
            }
            set{
                FriendlyNamesOfFields = value;
            }
        }

        public string FieldTypes
        {
            get{
                return TypesOfFields;
            }
            set{
                TypesOfFields = value;
            }
        }
    
        public System.Web.UI.WebControls.Label PageErrorTextLabel
        {
            get{
                return _pageErrorLabel;
            }
            set{
                _pageErrorLabel = value;
            }
        }

        public DBInterfacePage()
        {
            _connection = new DBConnection(this);
        }

        

        protected override void OnInit( EventArgs e )
        {
            base.OnInit(e);
            if( DBRegion != null )
                DBRegion.SetConnection( _connection );
        }

        protected void BindData()
        {
            if( DBRegion != null )
            {
                DBRegion.DataBind();
            }
        }

        public void ErrorMessage(string errorText)
        {
            if(PageErrorTextLabel == null)
            {
                return;
            }

            
            if(DebugOn)
            {
                if(PageErrorTextLabel.Text.Length == 0)
                {
                    PageErrorTextLabel.Text = "<B><%IDS_DBREGION_ASPNET_DEBUG_MESSAGES_LABEL%></B><br>";
                }
                PageErrorTextLabel.Text += errorText + "<br>";
            }
            else
            {
                PageErrorTextLabel.Text = 
                    "<%IDS_DBREGION_ERROR_DEFAULT_MESSAGE%>";
            }
        }

        public void ResetErrorMessages()
        {
            if(PageErrorTextLabel != null)
            {
                PageErrorTextLabel.Text = "";
            }
        }

        public virtual void UseControls()
        {
            _fieldNamesCollection = (StringCollection)Session["FieldNames"];
            _fieldFriendlyNamesCollection = (StringCollection)Session["FieldFriendlyNames"];
            _fieldTypesCollection = (StringCollection)Session["FieldTypes"];
            _fieldDefaultsCollection = (StringCollection)Session["FieldDefaults"];

            if(_fieldNamesCollection == null || _fieldTypesCollection == null  || _fieldFriendlyNamesCollection == null)
            {
                GetFieldData();
            }
        }

        protected virtual void  GetFieldData()
        {
            string sFieldNameList;
            string sFieldFriendList;
            string sFieldTypeList;
            string sFieldDefaultsList;
            if( FieldNames != null )
            {
                sFieldNameList = FieldNames;
            }
            else
            {
                sFieldNameList = ConfigurationSettings.AppSettings["FieldNames"];
            }
            if( FieldFriendlyNames != null)
            {
                sFieldFriendList = FieldFriendlyNames;
            }
            else
            {
                sFieldFriendList = ConfigurationSettings.AppSettings["FieldFriendlyNames"];
            }
            if( FieldTypes != null )
            {
                sFieldTypeList = FieldTypes;
            }
            else
            {
                sFieldTypeList = ConfigurationSettings.AppSettings["FieldTypes"];
            }
            if( FieldDefaults != null )
            {
                sFieldDefaultsList = FieldDefaults;
            }
            else
            {
                sFieldDefaultsList = ConfigurationSettings.AppSettings["FieldDefaults"];
            }
			
			
            int nNameComma, nFriendComma, nTypeComma, nDefaultComma;

            _fieldNamesCollection = new StringCollection();
            _fieldFriendlyNamesCollection = new StringCollection();
            _fieldTypesCollection = new StringCollection();
           
            if(sFieldDefaultsList != null)
            {
                _fieldDefaultsCollection = new StringCollection();
            }

            while((nNameComma=sFieldNameList.IndexOf(",")) != -1 
                && (nFriendComma = sFieldFriendList.IndexOf(",")) != -1
                && (nTypeComma=sFieldTypeList.IndexOf(",")) != -1 )
            {
                if(_fieldDefaultsCollection != null)
                {
                    if((nDefaultComma=sFieldDefaultsList.IndexOf(",")) == -1)
                    {
                        break;
                    }
                        
                    _fieldDefaultsCollection.Add(sFieldDefaultsList.Substring(0,nDefaultComma));
                    sFieldDefaultsList = sFieldDefaultsList.Substring(nDefaultComma+1);
                    if(sFieldDefaultsList == null)
                    {
                        sFieldDefaultsList = string.Empty;
                    }
                }
                _fieldNamesCollection.Add(sFieldNameList.Substring(0,nNameComma));
                sFieldNameList = sFieldNameList.Substring(nNameComma+1);
                _fieldFriendlyNamesCollection.Add(sFieldFriendList.Substring(0,nFriendComma));
                sFieldFriendList = sFieldFriendList.Substring(nFriendComma+1);
                _fieldTypesCollection.Add(sFieldTypeList.Substring(0,nTypeComma));
                sFieldTypeList = sFieldTypeList.Substring(nTypeComma+1);
            }
            _fieldNamesCollection.Add(sFieldNameList);
            _fieldFriendlyNamesCollection.Add(sFieldFriendList);
            _fieldTypesCollection.Add(sFieldTypeList);
            
            if(_fieldDefaultsCollection != null)
                _fieldDefaultsCollection.Add(sFieldDefaultsList);

            Session["FieldNames"] = _fieldNamesCollection;
            Session["FieldFriendNames"] = _fieldFriendlyNamesCollection;
            Session["FieldTypes"] = _fieldTypesCollection;
            Session["FieldDefaults"] = _fieldDefaultsCollection;

            if( sFieldNameList.IndexOf(",") != -1 &&
                sFieldFriendList.IndexOf(",") != -1 &&
                sFieldTypeList.IndexOf(",") != -1 &&
                ( _fieldDefaultsCollection!=null && sFieldDefaultsList.IndexOf(",") != -1 ) )
            {
                ErrorMessage("<%IDS_DBREGION_ASPNET_ERROR_FIELDS_MISMATCH%>");
            }
        }

        private string GetControlValue( Control controlParent, int index )
        {
            Control ctl = controlParent.FindControl( _fieldTypesCollection[index] + _fieldFriendlyNamesCollection[index] );
            if( ctl == null && (_fieldTypesCollection[index] + _fieldFriendlyNamesCollection[index]).Length != 0 )
            {
                ErrorMessage( "<%IDS_DBREGION_ASPNET_ERROR_NOCONTROLFOUND%>" );
                return string.Empty;
            }
            if(_fieldTypesCollection[index].Equals("txt"))
            {
                return ((TextBox)ctl).Text;
            }
            else if(_fieldTypesCollection[index].Equals("rdo"))
            {
                ListItem item = ((RadioButtonList)ctl).SelectedItem;
                if(item != null)
                {
                    return item.Value;
                }
                else 
                {
                    return null;
                }
            }
            else if(_fieldTypesCollection[index].Equals("ddl"))
            {
                ListItem item = ((DropDownList)ctl).SelectedItem;
                if(item != null)
                {
                    return item.Value;
                }
                else
                {
                    return null;
                }
            }
            else if(_fieldTypesCollection[index].Equals("chk"))
            {  
                    return ((CheckBox)ctl).Checked ? "True" : "False" ;
            }

            return string.Empty;
        }

        private void SetControlValue( Control parent, int index, string sValue )
        {
            Control control = parent.FindControl( _fieldTypesCollection[index] + _fieldFriendlyNamesCollection[index] );
            if( control == null && (_fieldTypesCollection[index] + _fieldFriendlyNamesCollection[index]).Length == 0 )
            {
                ErrorMessage( "<%IDS_DBREGION_ASPNET_ERROR_NOCONTROLFOUND%>" );
                return;
            }

            if(_fieldTypesCollection[index].Equals("txt"))
                ((TextBox)control).Text = sValue;
            else if(_fieldTypesCollection[index].Equals("rdo"))
            {
                if(((RadioButtonList)control).SelectedIndex != -1)
                {
                    ((RadioButtonList)control).Items[((RadioButtonList)control).SelectedIndex].Selected = false;
                }

                if( sValue.Length == 0 )
                {
                    ((RadioButtonList)control).SelectedIndex = -1;
                    return;
                }
                ListItem item = ((RadioButtonList)control).Items.FindByValue( sValue );
                if(item != null)
                {
                    item.Selected = true;
                }
                else
                {
                    ErrorMessage( "<%IDS_DBREGION_ASPNET_ERROR_NOT_AN_OPTION%>");
                }
            }
            else if(_fieldTypesCollection[index].Equals("ddl"))
            {
                if( sValue.Length == 0 )
                {
                    ((DropDownList)control).SelectedIndex = -1;
                    return;
                }
                ListItem item = ((DropDownList)control).Items.FindByValue( sValue );
                if(item != null)
                {
                    item.Selected = true;
                }
                else
                {
                    ErrorMessage("<%IDS_DBREGION_ASPNET_ERROR_NOT_AN_OPTION%>");
                }
            }
            else if(_fieldTypesCollection[index].Equals("chk"))
            {
               
                ((CheckBox)control).Checked = Convert.ToBoolean( sValue, CultureInfo.InvariantCulture );
            }
        }

        public void FillRowWithControls(DataRow row, Control controlParent)
        {
            FillRowWithControls( row, controlParent, false );
        }

        public bool FillRowWithControls(DataRow row, Control parent, bool checkUniqueKey)
        {
            if(_fieldNamesCollection == null || _fieldTypesCollection == null)
                return false;

            if(checkUniqueKey)
            {
                for( int i = 0; i < _fieldNamesCollection.Count; i++ )
                    if( _fieldNamesCollection[i].Equals( _connection.TableKey ) )
                    {
                        string sKeySearch = "[" + _connection.TableKey + "]='" 
                            + GetControlValue( parent, i ) + "'";
                        if( _connection.GetDataSet(true).Tables[0].Select( sKeySearch ).GetLength( 0 ) != 0 )
                        {
                            return false;
                        }
                        else
                        {
                            break;
                        }
                    }
            }

            for(int i=0; i<_fieldNamesCollection.Count; i++)
            {
                try{
                    if( _fieldNamesCollection[i].Length == 0 )
                        continue;

                    string curString = GetControlValue( parent, i );
                    if( ( curString != null ) && ( curString.Length != 0 ) )
                    {
                        row[_fieldNamesCollection[i]] = curString;
                    }
                    else
                    {
                        row[_fieldNamesCollection[i]] = DBNull.Value;
                    }
                }
                catch( FormatException ex ){
                    ErrorMessage("<%IDS_DBREGION_ASPNET_ERROR_WRITING%>");
                }
            }

            return true;
        }

        public void FillControlsWithRow(Control controlParent, DataRow row)
        {
            if(_fieldNamesCollection == null || _fieldTypesCollection == null)
                return;
            
            int i=0;

            try{
                for(; i<_fieldNamesCollection.Count; i++)
                {
                    if( _fieldNamesCollection[i].Length == 0 )
                        continue;

                    SetControlValue( controlParent, i, row[_fieldNamesCollection[i]].ToString() );
                }
            }
            catch( FormatException ex ){
                ErrorMessage( "<%IDS_DBREGION_ASPNET_ERROR_READING%>" );
            }
        }

        public void FillControlsWithDefaults(Control controlParent)
        {
            if(_fieldNamesCollection == null || _fieldTypesCollection == null)
            {
                return;
            }

            int i = 0;
            if(_fieldDefaultsCollection == null)
            {
                ErrorMessage("<%IDS_DBREGION_ASPNET_ERROR_NO_DEFAULTS%>");
                _fieldDefaultsCollection = new StringCollection();
                for(i = 0; i<_fieldNamesCollection.Count; i++)
                    _fieldDefaultsCollection.Add("");
            }

            try{
                for(i = 0; i<_fieldNamesCollection.Count; i++)
                {
                    if( _fieldNamesCollection[i].Length == 0 )
                    {
                        continue;
                    }

                    SetControlValue( controlParent, i, _fieldDefaultsCollection[i] );
                }
            }
            catch( FormatException ex ){
                ErrorMessage( "<%IDS_DBREGION_ASPNET_ERROR_READING%>");
            }
        }
    }

    /* This class provides additional functionality over DBInterfacePage in order to enable the user to do full
                                                             * edits and deletes of data as well as 
                                                             */
    public abstract class DBEditor : DBInterfacePage
    {
        
        private Button _addNewRecordButton;
        private Button _cancelChangeButton;
        private Button _resetRecordButton;
        private Button _submitChangeButton;
        private DataGrid _resultsGrid;
        
        private HtmlInputButton _deleteRecordButton;
        private HtmlGenericControl _editorPanel;
        private HtmlGenericControl _keyEditPanel;
    
        
       
        public Button AddNewRecordButton
        {
            get{
                return _addNewRecordButton;
            }
            set{
                _addNewRecordButton = value;
            }
        }
        
        public Button CancelChangeButton
        {
            get{
                return _cancelChangeButton;
            }
            set{
                _cancelChangeButton = value;
            }
        }
        
        public Button ResetRecordButton
        {
            get{
                return _resetRecordButton;
            }
            set{
                _resetRecordButton = value;
            }
        }
        public Button SubmitChangeButton
        {
            get{
                return _submitChangeButton;
            }
            set{
                _submitChangeButton = value;
            }
        }
       
        
        public DataGrid ResultsGrid
        {
            get{
                return _resultsGrid;
            }
            set{
                _resultsGrid = value;
            }
        }
        
        public HtmlInputButton DeleteRecordButton
        {
            get{
                return _deleteRecordButton;
            }
            set{
                _deleteRecordButton = value;
            }
        }
        public HtmlGenericControl EditorPanel
        {
            get{
                return _editorPanel;
            }
            set{
                _editorPanel = value;
            }
        }
        public HtmlGenericControl KeyEditPanel
        {
            get{
                return _keyEditPanel;
            }
            set{
                _keyEditPanel = value;
            }
        }


        private void OnLoadPage(object sender, System.EventArgs e)
        {
            InitEditor();

            if(!IsPostBack)
            {
                BindData();
                SetEditorState(false, false);
            }
            else if(!Connection.HasCache())
                Response.Redirect("session_expired.aspx");

            ResetErrorMessages();
        }

        public abstract void InitEditor();

        //Sets the enabled/disabled state of the detail and editing view of the
        //editor. 
        //Params:
        //    isEnabled determines whether or not the view should be visible and enabled
        //    isAdding determine whether or not the view is adding a new record, or updating
        //             an existing record.
        protected void SetEditorState(bool isEnabled, bool isAdding)
        {
            EditorPanel.Visible = isEnabled;
            AddNewRecordButton.Enabled = !isEnabled;

            if( KeyEditPanel != null )
                KeyEditPanel.Visible = isAdding;
            DeleteRecordButton.Visible = !isAdding;

            if(isAdding)
                InitialValues(null);
        }

        //Sets the values of all controls to their starting value.
        //Params:
        //    row - determines what row to base the starting values on.
        //               If it's null, use FieldDefaults.
        //               If it's non-null, use  
        protected void InitialValues(DataRow row)
        {
            if(row == null)
                FillControlsWithDefaults(EditorPanel);
            else
                FillControlsWithRow(EditorPanel, row);
        }

        protected DataRow CurrentRow()
        {

            DataView theDataView = new DataView(Connection.GetDataSet(true).Tables[0]);
            theDataView.RowFilter = (String)Session["WorkingDataRow"];
            return theDataView[0].Row;
        }

        protected void ClickButtonAddNewRecord(Object sender, EventArgs e)
        {
            InitialValues(null);
            
            Session["AddingDataRow"] = "true";

            SetEditorState(true, true);
        }

        protected void ClickButtonResetRecord(Object sender, EventArgs e)
        {
            try{
                if(Session["AddingDataRow"] != null)
                {
                    InitialValues(null);
                }
                else
                {
                    InitialValues(CurrentRow());
                }
            }
            catch(RowNotInTableException notInTable){
                ErrorMessage(notInTable.Message);
                SetEditorState(false, false);
            }
        }


        protected void ClickButtonCancelChange(Object sender, EventArgs e)
        {
            Session["WorkingDataRow"] = null;
            SetEditorState(false, false);
        }

        protected void ClickButtonDeleteRecord(Object sender, EventArgs e)
        {
            try{
                DataRow row = CurrentRow();

                if(row != null)
                    row.Delete();

                Session["WorkingDataRow"] = null;
                Connection.SaveChangesToDatabase();
                BindData();

                SetEditorState(false, false);
            }
            catch(ApplicationException dbi){
                ErrorMessage (dbi.Message);
            }
        }

        protected void ClickButtonSubmitChange(Object sender, EventArgs e)
        {
            try{
                DataRow row;
                bool isAdding = Session["AddingDataRow"] != null;
                if(isAdding)
                {
                    row = Connection.GetDataSet(true).Tables[0].NewRow();
                }
                else
                {
                    row = CurrentRow();
                }
                if(row == null)
                {
                    ErrorMessage(
                        "<%IDS_DBREGION_ASPNET_ERROR_SESSION_DAMAGED%>");
                    ClickButtonCancelChange(sender,e);
                }
                else
                {
                    row.BeginEdit();

                    if( FillRowWithControls(row, EditorPanel, isAdding ) )
                    {
                        row.EndEdit();
                        if(isAdding)
                        {
                            Connection.GetDataSet(true).Tables[0].Rows.Add(row);
                        }                    
                        Connection.SaveChangesToDatabase();
                        Connection.RefreshCache();
                        BindData();

                        Session["WorkingDataRow"] = null;
                        Session["AddingDataRow"] = null;
                        SetEditorState(false, false);
                    }
                    else
                    {
                        row.CancelEdit();
                        ErrorMessage("<%IDS_DBREGION_ASPNET_ERROR_UNIQUENESS%>");
                    }
                }
            }
            catch(ApplicationException dbi){
                ErrorMessage (dbi.Message);
            }
        }

        protected void CommandImageEdit(Object sender, CommandEventArgs e)
        {
            DataView theDataView = new DataView(Connection.GetDataSet(true).Tables[0]);
            StringBuilder sb = new StringBuilder("[");
            sb.Append( Connection.TableKey );
            sb.Append( "]='");
            sb.Append( e.CommandName );
            sb.Append( "'" );
            theDataView.RowFilter = sb.ToString();


            if(theDataView.Count == 0)
            {
                ErrorMessage("<%IDS_DBREGION_ASPNET_ERROR_ROW_NOT_IN_CACHE%>");
                Connection.RefreshCache();
                BindData();
            }
            else
            {    
                InitialValues(theDataView[0].Row);
                Session["WorkingDataRow"] = sb.ToString();
				Session["AddingDataRow"] = null;
                SetEditorState(true, false);
            }
        }

        override protected void OnInit(EventArgs e)
        {
            InitializeComponent();
            base.OnInit(e);
        }

        private void InitializeComponent()
        {    
            this.Load += new System.EventHandler(this.OnLoadPage);
        }
    }

    public abstract class DBRegionBase : System.Web.UI.UserControl 
    {
        public abstract override void DataBind();
        public abstract void SetConnection( DBConnection theConnection );
    }
}
