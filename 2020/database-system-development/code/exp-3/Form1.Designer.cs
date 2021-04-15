namespace exp_3
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.submit_btn = new System.Windows.Forms.Button();
            this.cancel_btn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.student_id_textbox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.refresh_btn = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.student_name_label = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.course_selected_sum_label = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.score_selected_sum_label = new System.Windows.Forms.Label();
            this.oleDbSelectCommand1 = new System.Data.OleDb.OleDbCommand();
            this.oleDbConnection1 = new System.Data.OleDb.OleDbConnection();
            this.oleDbInsertCommand1 = new System.Data.OleDb.OleDbCommand();
            this.oleDbUpdateCommand1 = new System.Data.OleDb.OleDbCommand();
            this.oleDbDeleteCommand1 = new System.Data.OleDb.OleDbCommand();
            this.oleDbDataAdapter1 = new System.Data.OleDb.OleDbDataAdapter();
            this.oleDbSelectCommand2 = new System.Data.OleDb.OleDbCommand();
            this.oleDbDataAdapter2 = new System.Data.OleDb.OleDbDataAdapter();
            this.exit_btn = new System.Windows.Forms.Button();
            this.add_btn = new System.Windows.Forms.Button();
            this.remove_btn = new System.Windows.Forms.Button();
            this.oleDbSelectCommand3 = new System.Data.OleDb.OleDbCommand();
            this.oleDbDataAdapter3 = new System.Data.OleDb.OleDbDataAdapter();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.course_remained_sum_label = new System.Windows.Forms.Label();
            this.score_remained_sum_label = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.status_label = new System.Windows.Forms.Label();
            this.dataGridSelectedCourse = new System.Windows.Forms.DataGrid();
            this.dataSetCourseSelected1 = new exp_3.DataSetCourseSelected();
            this.dataGridAllCourse = new System.Windows.Forms.DataGrid();
            this.dataSetCourse1 = new exp_3.DataSetCourse();
            this.dataSetStudent1 = new exp_3.DataSetStudent();
            this.save_btn = new System.Windows.Forms.Button();
            this.oleDbSelectCommand4 = new System.Data.OleDb.OleDbCommand();
            this.oleDbInsertCommand2 = new System.Data.OleDb.OleDbCommand();
            this.oleDbDataAdapter4 = new System.Data.OleDb.OleDbDataAdapter();
            this.dataSetCourseAdded1 = new exp_3.DataSetCourseAdded();
            this.oleDbCommand1 = new System.Data.OleDb.OleDbCommand();
            this.label10 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridSelectedCourse)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetCourseSelected1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridAllCourse)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetCourse1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetStudent1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetCourseAdded1)).BeginInit();
            this.SuspendLayout();
            // 
            // submit_btn
            // 
            this.submit_btn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.submit_btn.Enabled = false;
            this.submit_btn.Location = new System.Drawing.Point(842, 786);
            this.submit_btn.Name = "submit_btn";
            this.submit_btn.Size = new System.Drawing.Size(178, 62);
            this.submit_btn.TabIndex = 1;
            this.submit_btn.Text = "提交";
            this.submit_btn.UseVisualStyleBackColor = true;
            this.submit_btn.Click += new System.EventHandler(this.submit_btn_Click);
            // 
            // cancel_btn
            // 
            this.cancel_btn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cancel_btn.Enabled = false;
            this.cancel_btn.Location = new System.Drawing.Point(1046, 786);
            this.cancel_btn.Name = "cancel_btn";
            this.cancel_btn.Size = new System.Drawing.Size(178, 62);
            this.cancel_btn.TabIndex = 2;
            this.cancel_btn.Text = "取消";
            this.cancel_btn.UseVisualStyleBackColor = true;
            this.cancel_btn.Click += new System.EventHandler(this.cancel_btn_Click);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 9F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(811, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(135, 24);
            this.label1.TabIndex = 4;
            this.label1.Text = "已选课程：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 24);
            this.label2.TabIndex = 5;
            this.label2.Text = "学号：";
            // 
            // student_id_textbox
            // 
            this.student_id_textbox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.student_id_textbox.Location = new System.Drawing.Point(102, 50);
            this.student_id_textbox.Name = "student_id_textbox";
            this.student_id_textbox.Size = new System.Drawing.Size(466, 35);
            this.student_id_textbox.TabIndex = 6;
            this.student_id_textbox.TextChanged += new System.EventHandler(this.student_id_textbox_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("宋体", 9F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(12, 340);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(160, 24);
            this.label3.TabIndex = 7;
            this.label3.Text = "可选选课程：";
            // 
            // refresh_btn
            // 
            this.refresh_btn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.refresh_btn.Location = new System.Drawing.Point(585, 48);
            this.refresh_btn.Name = "refresh_btn";
            this.refresh_btn.Size = new System.Drawing.Size(205, 45);
            this.refresh_btn.TabIndex = 8;
            this.refresh_btn.Text = "刷新";
            this.refresh_btn.UseVisualStyleBackColor = true;
            this.refresh_btn.Click += new System.EventHandler(this.refresh_btn_Click);
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(14, 122);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(130, 24);
            this.label4.TabIndex = 9;
            this.label4.Text = "学生姓名：";
            // 
            // student_name_label
            // 
            this.student_name_label.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.student_name_label.AutoSize = true;
            this.student_name_label.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.student_name_label.Location = new System.Drawing.Point(174, 122);
            this.student_name_label.Name = "student_name_label";
            this.student_name_label.Size = new System.Drawing.Size(110, 24);
            this.student_name_label.TabIndex = 10;
            this.student_name_label.Text = "未知学生";
            // 
            // label5
            // 
            this.label5.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(14, 176);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(154, 24);
            this.label5.TabIndex = 11;
            this.label5.Text = "已选课程数：";
            // 
            // course_selected_sum_label
            // 
            this.course_selected_sum_label.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.course_selected_sum_label.AutoSize = true;
            this.course_selected_sum_label.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.course_selected_sum_label.Location = new System.Drawing.Point(174, 176);
            this.course_selected_sum_label.Name = "course_selected_sum_label";
            this.course_selected_sum_label.Size = new System.Drawing.Size(23, 24);
            this.course_selected_sum_label.TabIndex = 12;
            this.course_selected_sum_label.Text = "0";
            // 
            // label6
            // 
            this.label6.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(14, 230);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(154, 24);
            this.label6.TabIndex = 13;
            this.label6.Text = "已选学分数：";
            // 
            // score_selected_sum_label
            // 
            this.score_selected_sum_label.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.score_selected_sum_label.AutoSize = true;
            this.score_selected_sum_label.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.score_selected_sum_label.Location = new System.Drawing.Point(174, 230);
            this.score_selected_sum_label.Name = "score_selected_sum_label";
            this.score_selected_sum_label.Size = new System.Drawing.Size(23, 24);
            this.score_selected_sum_label.TabIndex = 14;
            this.score_selected_sum_label.Text = "0";
            // 
            // oleDbSelectCommand1
            // 
            this.oleDbSelectCommand1.CommandText = "select * from Student";
            this.oleDbSelectCommand1.Connection = this.oleDbConnection1;
            // 
            // oleDbConnection1
            // 
            this.oleDbConnection1.ConnectionString = "Provider=SQLNCLI11;Data Source=DESKTOP-JJFIP2I;Integrated Security=SSPI;Initial C" +
    "atalog=CourseManagement";
            // 
            // oleDbInsertCommand1
            // 
            this.oleDbInsertCommand1.CommandText = "INSERT INTO [Student] ([id], [name]) VALUES (?, ?)";
            this.oleDbInsertCommand1.Connection = this.oleDbConnection1;
            this.oleDbInsertCommand1.Parameters.AddRange(new System.Data.OleDb.OleDbParameter[] {
            new System.Data.OleDb.OleDbParameter("id", System.Data.OleDb.OleDbType.Char, 0, "id"),
            new System.Data.OleDb.OleDbParameter("name", System.Data.OleDb.OleDbType.VarChar, 0, "name")});
            // 
            // oleDbUpdateCommand1
            // 
            this.oleDbUpdateCommand1.CommandText = "UPDATE [Student] SET [id] = ?, [name] = ? WHERE (([id] = ?) AND ([name] = ?))";
            this.oleDbUpdateCommand1.Connection = this.oleDbConnection1;
            this.oleDbUpdateCommand1.Parameters.AddRange(new System.Data.OleDb.OleDbParameter[] {
            new System.Data.OleDb.OleDbParameter("id", System.Data.OleDb.OleDbType.Char, 0, "id"),
            new System.Data.OleDb.OleDbParameter("name", System.Data.OleDb.OleDbType.VarChar, 0, "name"),
            new System.Data.OleDb.OleDbParameter("Original_id", System.Data.OleDb.OleDbType.Char, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "id", System.Data.DataRowVersion.Original, null),
            new System.Data.OleDb.OleDbParameter("Original_name", System.Data.OleDb.OleDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "name", System.Data.DataRowVersion.Original, null)});
            // 
            // oleDbDeleteCommand1
            // 
            this.oleDbDeleteCommand1.CommandText = "DELETE FROM [Student] WHERE (([id] = ?) AND ([name] = ?))";
            this.oleDbDeleteCommand1.Connection = this.oleDbConnection1;
            this.oleDbDeleteCommand1.Parameters.AddRange(new System.Data.OleDb.OleDbParameter[] {
            new System.Data.OleDb.OleDbParameter("Original_id", System.Data.OleDb.OleDbType.Char, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "id", System.Data.DataRowVersion.Original, null),
            new System.Data.OleDb.OleDbParameter("Original_name", System.Data.OleDb.OleDbType.VarChar, 0, System.Data.ParameterDirection.Input, false, ((byte)(0)), ((byte)(0)), "name", System.Data.DataRowVersion.Original, null)});
            // 
            // oleDbDataAdapter1
            // 
            this.oleDbDataAdapter1.DeleteCommand = this.oleDbDeleteCommand1;
            this.oleDbDataAdapter1.InsertCommand = this.oleDbInsertCommand1;
            this.oleDbDataAdapter1.SelectCommand = this.oleDbSelectCommand1;
            this.oleDbDataAdapter1.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
            new System.Data.Common.DataTableMapping("Table", "Student", new System.Data.Common.DataColumnMapping[] {
                        new System.Data.Common.DataColumnMapping("id", "id"),
                        new System.Data.Common.DataColumnMapping("name", "name")})});
            this.oleDbDataAdapter1.UpdateCommand = this.oleDbUpdateCommand1;
            // 
            // oleDbSelectCommand2
            // 
            this.oleDbSelectCommand2.CommandText = resources.GetString("oleDbSelectCommand2.CommandText");
            this.oleDbSelectCommand2.Connection = this.oleDbConnection1;
            // 
            // oleDbDataAdapter2
            // 
            this.oleDbDataAdapter2.SelectCommand = this.oleDbSelectCommand2;
            this.oleDbDataAdapter2.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
            new System.Data.Common.DataTableMapping("Table", "Course", new System.Data.Common.DataColumnMapping[] {
                        new System.Data.Common.DataColumnMapping("ID", "ID"),
                        new System.Data.Common.DataColumnMapping("Course name", "Course name"),
                        new System.Data.Common.DataColumnMapping("Score", "Score"),
                        new System.Data.Common.DataColumnMapping("Teacher name", "Teacher name"),
                        new System.Data.Common.DataColumnMapping("Course time", "Course time")})});
            // 
            // exit_btn
            // 
            this.exit_btn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.exit_btn.Location = new System.Drawing.Point(1250, 786);
            this.exit_btn.Name = "exit_btn";
            this.exit_btn.Size = new System.Drawing.Size(178, 62);
            this.exit_btn.TabIndex = 15;
            this.exit_btn.Text = "退出";
            this.exit_btn.UseVisualStyleBackColor = true;
            this.exit_btn.Click += new System.EventHandler(this.exit_btn_Click);
            // 
            // add_btn
            // 
            this.add_btn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.add_btn.Enabled = false;
            this.add_btn.Location = new System.Drawing.Point(12, 786);
            this.add_btn.Name = "add_btn";
            this.add_btn.Size = new System.Drawing.Size(178, 62);
            this.add_btn.TabIndex = 16;
            this.add_btn.Text = "添加";
            this.add_btn.UseVisualStyleBackColor = true;
            this.add_btn.Click += new System.EventHandler(this.add_btn_Click);
            // 
            // remove_btn
            // 
            this.remove_btn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.remove_btn.Enabled = false;
            this.remove_btn.Location = new System.Drawing.Point(216, 786);
            this.remove_btn.Name = "remove_btn";
            this.remove_btn.Size = new System.Drawing.Size(178, 62);
            this.remove_btn.TabIndex = 17;
            this.remove_btn.Text = "移除";
            this.remove_btn.UseVisualStyleBackColor = true;
            this.remove_btn.Click += new System.EventHandler(this.remove_btn_Click);
            // 
            // oleDbSelectCommand3
            // 
            this.oleDbSelectCommand3.CommandText = resources.GetString("oleDbSelectCommand3.CommandText");
            this.oleDbSelectCommand3.Connection = this.oleDbConnection1;
            // 
            // oleDbDataAdapter3
            // 
            this.oleDbDataAdapter3.SelectCommand = this.oleDbSelectCommand3;
            this.oleDbDataAdapter3.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
            new System.Data.Common.DataTableMapping("Table", "Course", new System.Data.Common.DataColumnMapping[] {
                        new System.Data.Common.DataColumnMapping("ID", "ID"),
                        new System.Data.Common.DataColumnMapping("Course name", "Course name"),
                        new System.Data.Common.DataColumnMapping("Score", "Score"),
                        new System.Data.Common.DataColumnMapping("Teacher name", "Teacher name"),
                        new System.Data.Common.DataColumnMapping("Course time", "Course time")})});
            // 
            // label7
            // 
            this.label7.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(230, 176);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(154, 24);
            this.label7.TabIndex = 18;
            this.label7.Text = "可选课程数：";
            // 
            // label8
            // 
            this.label8.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(230, 230);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(154, 24);
            this.label8.TabIndex = 19;
            this.label8.Text = "可选学分数：";
            // 
            // course_remained_sum_label
            // 
            this.course_remained_sum_label.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.course_remained_sum_label.AutoSize = true;
            this.course_remained_sum_label.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.course_remained_sum_label.Location = new System.Drawing.Point(390, 176);
            this.course_remained_sum_label.Name = "course_remained_sum_label";
            this.course_remained_sum_label.Size = new System.Drawing.Size(135, 24);
            this.course_remained_sum_label.TabIndex = 20;
            this.course_remained_sum_label.Text = "未知课程数";
            // 
            // score_remained_sum_label
            // 
            this.score_remained_sum_label.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.score_remained_sum_label.AutoSize = true;
            this.score_remained_sum_label.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.score_remained_sum_label.Location = new System.Drawing.Point(390, 230);
            this.score_remained_sum_label.Name = "score_remained_sum_label";
            this.score_remained_sum_label.Size = new System.Drawing.Size(135, 24);
            this.score_remained_sum_label.TabIndex = 21;
            this.score_remained_sum_label.Text = "未知学分数";
            // 
            // label9
            // 
            this.label9.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(14, 284);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(130, 24);
            this.label9.TabIndex = 22;
            this.label9.Text = "选课状态：";
            // 
            // status_label
            // 
            this.status_label.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.status_label.AutoSize = true;
            this.status_label.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.status_label.Location = new System.Drawing.Point(174, 284);
            this.status_label.Name = "status_label";
            this.status_label.Size = new System.Drawing.Size(110, 24);
            this.status_label.TabIndex = 23;
            this.status_label.Text = "未知状态";
            // 
            // dataGridSelectedCourse
            // 
            this.dataGridSelectedCourse.AllowSorting = false;
            this.dataGridSelectedCourse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridSelectedCourse.DataMember = "Course";
            this.dataGridSelectedCourse.DataSource = this.dataSetCourseSelected1;
            this.dataGridSelectedCourse.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridSelectedCourse.Location = new System.Drawing.Point(815, 50);
            this.dataGridSelectedCourse.Name = "dataGridSelectedCourse";
            this.dataGridSelectedCourse.ReadOnly = true;
            this.dataGridSelectedCourse.Size = new System.Drawing.Size(615, 324);
            this.dataGridSelectedCourse.TabIndex = 3;
            // 
            // dataSetCourseSelected1
            // 
            this.dataSetCourseSelected1.DataSetName = "DataSetCourseSelected";
            this.dataSetCourseSelected1.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // dataGridAllCourse
            // 
            this.dataGridAllCourse.AllowSorting = false;
            this.dataGridAllCourse.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridAllCourse.CausesValidation = false;
            this.dataGridAllCourse.DataMember = "Course";
            this.dataGridAllCourse.DataSource = this.dataSetCourse1;
            this.dataGridAllCourse.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGridAllCourse.Location = new System.Drawing.Point(12, 380);
            this.dataGridAllCourse.Name = "dataGridAllCourse";
            this.dataGridAllCourse.PreferredColumnWidth = 130;
            this.dataGridAllCourse.ReadOnly = true;
            this.dataGridAllCourse.Size = new System.Drawing.Size(1418, 400);
            this.dataGridAllCourse.TabIndex = 0;
            this.dataGridAllCourse.Tag = "";
            // 
            // dataSetCourse1
            // 
            this.dataSetCourse1.DataSetName = "DataSetCourse";
            this.dataSetCourse1.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // dataSetStudent1
            // 
            this.dataSetStudent1.DataSetName = "DataSetStudent";
            this.dataSetStudent1.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // save_btn
            // 
            this.save_btn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.save_btn.Enabled = false;
            this.save_btn.Location = new System.Drawing.Point(638, 786);
            this.save_btn.Name = "save_btn";
            this.save_btn.Size = new System.Drawing.Size(178, 62);
            this.save_btn.TabIndex = 24;
            this.save_btn.Text = "预选";
            this.save_btn.UseVisualStyleBackColor = true;
            this.save_btn.Click += new System.EventHandler(this.save_btn_Click);
            // 
            // oleDbSelectCommand4
            // 
            this.oleDbSelectCommand4.CommandText = "select student_id, course_id, status from CourseSelected";
            this.oleDbSelectCommand4.Connection = this.oleDbConnection1;
            // 
            // oleDbInsertCommand2
            // 
            this.oleDbInsertCommand2.CommandText = "INSERT INTO [CourseSelected] ([student_id], [course_id], [status]) VALUES (?, ?, " +
    "?)";
            this.oleDbInsertCommand2.Connection = this.oleDbConnection1;
            this.oleDbInsertCommand2.Parameters.AddRange(new System.Data.OleDb.OleDbParameter[] {
            new System.Data.OleDb.OleDbParameter("student_id", System.Data.OleDb.OleDbType.Char, 0, "student_id"),
            new System.Data.OleDb.OleDbParameter("course_id", System.Data.OleDb.OleDbType.Char, 0, "course_id"),
            new System.Data.OleDb.OleDbParameter("status", System.Data.OleDb.OleDbType.Integer, 0, "status")});
            // 
            // oleDbDataAdapter4
            // 
            this.oleDbDataAdapter4.DeleteCommand = this.oleDbCommand1;
            this.oleDbDataAdapter4.InsertCommand = this.oleDbInsertCommand2;
            this.oleDbDataAdapter4.SelectCommand = this.oleDbSelectCommand4;
            this.oleDbDataAdapter4.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
            new System.Data.Common.DataTableMapping("Table", "CourseSelected", new System.Data.Common.DataColumnMapping[] {
                        new System.Data.Common.DataColumnMapping("student_id", "student_id"),
                        new System.Data.Common.DataColumnMapping("course_id", "course_id"),
                        new System.Data.Common.DataColumnMapping("status", "status")})});
            // 
            // dataSetCourseAdded1
            // 
            this.dataSetCourseAdded1.DataSetName = "DataSetCourseAdded";
            this.dataSetCourseAdded1.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // oleDbCommand1
            // 
            this.oleDbCommand1.Connection = this.oleDbConnection1;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("宋体", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label10.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.label10.Location = new System.Drawing.Point(941, 22);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(448, 16);
            this.label10.TabIndex = 25;
            this.label10.Text = "在 Status 列中，Preselected 表示预选，Selected 表示已选";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1442, 860);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.save_btn);
            this.Controls.Add(this.status_label);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.score_remained_sum_label);
            this.Controls.Add(this.course_remained_sum_label);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.remove_btn);
            this.Controls.Add(this.add_btn);
            this.Controls.Add(this.exit_btn);
            this.Controls.Add(this.score_selected_sum_label);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.course_selected_sum_label);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.student_name_label);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.refresh_btn);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.student_id_textbox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dataGridSelectedCourse);
            this.Controls.Add(this.cancel_btn);
            this.Controls.Add(this.submit_btn);
            this.Controls.Add(this.dataGridAllCourse);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "选课管理";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridSelectedCourse)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetCourseSelected1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridAllCourse)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetCourse1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetStudent1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetCourseAdded1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGrid dataGridAllCourse;
        private System.Windows.Forms.Button submit_btn;
        private System.Windows.Forms.Button cancel_btn;
        private System.Windows.Forms.DataGrid dataGridSelectedCourse;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox student_id_textbox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button refresh_btn;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label student_name_label;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label course_selected_sum_label;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label score_selected_sum_label;
        private System.Data.OleDb.OleDbCommand oleDbSelectCommand1;
        private System.Data.OleDb.OleDbConnection oleDbConnection1;
        private System.Data.OleDb.OleDbCommand oleDbInsertCommand1;
        private System.Data.OleDb.OleDbCommand oleDbUpdateCommand1;
        private System.Data.OleDb.OleDbCommand oleDbDeleteCommand1;
        private System.Data.OleDb.OleDbDataAdapter oleDbDataAdapter1;
        private DataSetStudent dataSetStudent1;
        private DataSetCourse dataSetCourse1;
        private System.Data.OleDb.OleDbCommand oleDbSelectCommand2;
        private System.Data.OleDb.OleDbDataAdapter oleDbDataAdapter2;
        private System.Windows.Forms.Button exit_btn;
        private System.Windows.Forms.Button add_btn;
        private System.Windows.Forms.Button remove_btn;
        private DataSetCourseSelected dataSetCourseSelected1;
        private System.Data.OleDb.OleDbCommand oleDbSelectCommand3;
        private System.Data.OleDb.OleDbDataAdapter oleDbDataAdapter3;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label course_remained_sum_label;
        private System.Windows.Forms.Label score_remained_sum_label;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label status_label;
        private System.Windows.Forms.Button save_btn;
        private System.Data.OleDb.OleDbCommand oleDbSelectCommand4;
        private System.Data.OleDb.OleDbCommand oleDbInsertCommand2;
        private System.Data.OleDb.OleDbDataAdapter oleDbDataAdapter4;
        private DataSetCourseAdded dataSetCourseAdded1;
        private System.Data.OleDb.OleDbCommand oleDbCommand1;
        private System.Windows.Forms.Label label10;
    }
}

