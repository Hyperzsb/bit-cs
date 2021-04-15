using System;
using System.Collections;
using System.Data;
using System.Drawing;
using System.Windows.Forms;

namespace exp_3
{
    public partial class Form1 : Form
    {
        // 学生学号
        private String student_id;
        // 学生的已选课程数量
        private int course_selected_sum;
        // 学生的可选课程数量
        private int course_unselected_sum;
        // 增加课程列表
        private ArrayList course_confirm_list = new ArrayList();
        // 增加课程列表
        private ArrayList course_add_list = new ArrayList();
        // 移除课程列表
        private ArrayList course_remove_list = new ArrayList();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.oleDbDataAdapter2.Fill(dataSetCourse1);
        }

        private void UpdateStatus()
        {
            bool course_check = false;
            bool score_check = false;
            // 已选课程数量信息
            course_selected_sum = dataSetCourseSelected1.Tables["Course"].Rows.Count;
            course_selected_sum_label.Text = course_selected_sum.ToString();
            // 可选课程数量信息
            int course_remained_sum_min = 3 - course_selected_sum;
            int course_remained_sum_max = 5 - course_selected_sum;
            if (course_remained_sum_min > 0)
            {
                course_remained_sum_label.Text = "仍需选至少"+course_remained_sum_min.ToString()+"门课程";
                course_remained_sum_label.ForeColor = Color.Red;

            }
            else if (course_remained_sum_min <= 0 && course_remained_sum_max >= 0)
            {
                course_remained_sum_label.Text = "已选够课程，还可再选" + course_remained_sum_max.ToString() + "门课程";
                course_remained_sum_label.ForeColor = Color.Green;
                course_check = true;
            }
            else
            {
                course_remained_sum_label.Text = "已选课程数量达到上限！请退课！";
                course_remained_sum_label.ForeColor = Color.Red;
            }
            // 已选学分数量信息
            int score_selected_sum = 0;
            for (int i = 0; i < dataSetCourseSelected1.Tables["Course"].Rows.Count; i++)
                score_selected_sum += Int32.Parse(dataSetCourseSelected1.Tables["Course"].Rows[i]["Score"].ToString());
            score_selected_sum_label.Text = score_selected_sum.ToString();
            // 未选学分数量信息
            int score_remained_sum_min = 8 - score_selected_sum;
            int score_remained_sum_max = 12 - score_selected_sum;
            if (score_remained_sum_min > 0)
            {
                score_remained_sum_label.Text = "仍需修至少" + score_remained_sum_min.ToString() + "个学分";
                score_remained_sum_label.ForeColor = Color.Red;
            }
            else if (score_remained_sum_min <= 0 && score_remained_sum_max >= 0)
            {
                score_remained_sum_label.Text = "已修够学分，还可再修" + score_remained_sum_max.ToString() + "个学分";
                score_remained_sum_label.ForeColor = Color.Green;
                score_check = true;
            }
            else
            {
                score_remained_sum_label.Text = "已修学分数量达到上限！请退课！";
                score_remained_sum_label.ForeColor = Color.Red;
            }

            if (course_check && score_check)
            {
                status_label.Text = "可提交！";
                status_label.ForeColor = Color.Green;
                submit_btn.Enabled = true;
            }
            else
            {
                status_label.Text = "不可提交！";
                status_label.ForeColor = Color.Red;
                submit_btn.Enabled = false;
            }
        }

        private void student_id_textbox_TextChanged(object sender, EventArgs e)
        {
            // 判断学号是否输入完成，若完成调用更新函数
            if(student_id_textbox.Text.Length==10)
                refresh_btn_Click(null,null);
        }

        private void refresh_btn_Click(object sender, EventArgs e)
        {
            // 清空数据集缓存
            dataSetCourse1.Clear();
            dataSetCourseSelected1.Clear();
            dataSetCourseAdded1.Clear();

            // 获取学生姓名
            String whereStatment = " where id = '" + student_id_textbox.Text + "'";
            String oldSelectCommand = oleDbDataAdapter1.SelectCommand.CommandText;
            oleDbDataAdapter1.SelectCommand.CommandText = oldSelectCommand + whereStatment;
            dataSetStudent1.Clear();
            try
            {
                oleDbDataAdapter1.Fill(dataSetStudent1);
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
            // 判断是否存在该学生
            if (dataSetStudent1.Tables["Student"].Rows.Count == 0)
            {
                MessageBox.Show("查无此人！请检查输入的学号是否正确！");
                oleDbDataAdapter1.SelectCommand.CommandText = oldSelectCommand;
                return;
            }
            else
            {
                student_id = student_id_textbox.Text;
            }
            // 显示学生姓名
            student_name_label.Text = dataSetStudent1.Tables["Student"].Rows[0]["name"].ToString();
            oleDbDataAdapter1.SelectCommand.CommandText = oldSelectCommand;

            // 获取已选课程
            oleDbDataAdapter3.SelectCommand.CommandText = "select (case when CourseSelected.status = 0 then 'Preselected' when CourseSelected.status = 1 then 'Selected' end) as 'Status', " +
                                                          "Course.id as 'ID', Course.name as 'Course name' , Course.score as 'Score', Teacher.name as 'Teacher name', Course.time as 'Course time' " +
                                                          "from Course, Teacher, CourseSelected " +
                                                          "where Course.teacher_id = Teacher.id " +
                                                          "and Course.id = CourseSelected.course_id " +
                                                          "and CourseSelected.student_id = '" + student_id_textbox.Text + "' " +
                                                          "and Teacher.id in (select t.id from Teacher as t, TeachersForStudents as tfs where t.id = tfs.teacher_id)";
            dataSetCourseSelected1.Clear();
            try
            {
                oleDbDataAdapter3.Fill(dataSetCourseSelected1);
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }

            // 获取剩余可选课程
            oldSelectCommand = oleDbDataAdapter2.SelectCommand.CommandText;
            oleDbDataAdapter2.SelectCommand.CommandText = "select Course.id as 'ID', Course.name as 'Course name' , Course.score as 'Score', Teacher.name as 'Teacher name', Course.time as 'Course time' " +
                                                          "from Course, Teacher " +
                                                          "where Course.teacher_id = Teacher.id " +
                                                          "and Course.id not in(select cs.course_id from CourseSelected as cs where cs.student_id = '" + student_id_textbox.Text + "') " +
                                                          "and Teacher.id in (select t.id from Teacher as t, TeachersForStudents as tfs where t.id = tfs.teacher_id and tfs.student_id = '" + student_id_textbox.Text + "')";
            dataSetCourse1.Clear();
            try
            {
                oleDbDataAdapter2.Fill(dataSetCourse1);
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
            oleDbDataAdapter2.SelectCommand.CommandText = oldSelectCommand;
            course_unselected_sum = dataSetCourse1.Tables["Course"].Rows.Count;

            // 启用增删课及提交功能
            save_btn.Enabled = true;
            add_btn.Enabled = true;
            remove_btn.Enabled = true;
            submit_btn.Enabled = true;
            cancel_btn.Enabled = true;
            // 清空增删课信息表
            course_confirm_list.Clear();
            course_add_list.Clear();
            course_remove_list.Clear();
            // 更新标签状态
            UpdateStatus();
        }

        private void add_btn_Click(object sender, EventArgs e)
        {
            // 将课程信息从可选课表移动到已选课表中
            DataRow new_row = dataSetCourseSelected1.Tables["Course"].NewRow();
            new_row["ID"] = dataSetCourse1.Tables["Course"].Rows[dataGridAllCourse.CurrentRowIndex]["ID"];
            new_row["Course name"] = dataSetCourse1.Tables["Course"].Rows[dataGridAllCourse.CurrentRowIndex]["Course name"];
            new_row["Score"] = dataSetCourse1.Tables["Course"].Rows[dataGridAllCourse.CurrentRowIndex]["Score"];
            new_row["Teacher name"] = dataSetCourse1.Tables["Course"].Rows[dataGridAllCourse.CurrentRowIndex]["Teacher name"];
            new_row["Course time"] = dataSetCourse1.Tables["Course"].Rows[dataGridAllCourse.CurrentRowIndex]["Course time"];
            dataSetCourseSelected1.Tables["Course"].Rows.InsertAt(new_row, course_selected_sum++);
            course_add_list.Add(dataSetCourse1.Tables["Course"].Rows[dataGridAllCourse.CurrentRowIndex]["ID"]);
            dataSetCourse1.Tables["Course"].Rows.RemoveAt(dataGridAllCourse.CurrentRowIndex);

            // 更新标签状态
            UpdateStatus();
        }

        private void remove_btn_Click(object sender, EventArgs e)
        {
            // 将课程信息从已选课表中移动到可选课表中
            DataRow new_row = dataSetCourse1.Tables["Course"].NewRow();
            new_row["ID"] = dataSetCourseSelected1.Tables["Course"].Rows[dataGridSelectedCourse.CurrentRowIndex]["ID"];
            new_row["Course name"] = dataSetCourseSelected1.Tables["Course"].Rows[dataGridSelectedCourse.CurrentRowIndex]["Course name"];
            new_row["Score"] = dataSetCourseSelected1.Tables["Course"].Rows[dataGridSelectedCourse.CurrentRowIndex]["Score"];
            new_row["Teacher name"] = dataSetCourseSelected1.Tables["Course"].Rows[dataGridSelectedCourse.CurrentRowIndex]["Teacher name"];
            new_row["Course time"] = dataSetCourseSelected1.Tables["Course"].Rows[dataGridSelectedCourse.CurrentRowIndex]["Course time"];
            dataSetCourse1.Tables["Course"].Rows.InsertAt(new_row, course_unselected_sum++);
            course_remove_list.Add(dataSetCourseSelected1.Tables["Course"].Rows[dataGridSelectedCourse.CurrentRowIndex]["ID"]);
            dataSetCourseSelected1.Tables["Course"].Rows.RemoveAt(dataGridSelectedCourse.CurrentRowIndex);

            // 更新标签状态
            UpdateStatus();
        }

        private void save_btn_Click(object sender, EventArgs e)
        {
            bool status = true;
            try
            {
                // 遍历增加课程列表，并将包括的课程加入数据库的已选课程表中
                foreach (String course in course_add_list)
                {
                    DataRow new_row = dataSetCourseAdded1.Tables["CourseSelected"].NewRow();
                    new_row["student_id"] = student_id;
                    new_row["course_id"] = course;
                    new_row["status"] = 0;
                    dataSetCourseAdded1.Tables["CourseSelected"].Rows.InsertAt(new_row, 0);
                }
                oleDbDataAdapter4.Update(dataSetCourseAdded1, "CourseSelected");

                // 遍历删除课程列表，并将包括的课程移除出数据库的已选课程表
                foreach (String course in course_remove_list)
                {
                    String course_delete_command = "delete from CourseSelected WHERE student_id = '" + student_id + "' and course_id = '" + course + "'";

                    oleDbDataAdapter4.DeleteCommand.CommandText = course_delete_command;
                    oleDbDataAdapter4.DeleteCommand.Connection.Open();
                    oleDbDataAdapter4.DeleteCommand.ExecuteNonQuery();
                    oleDbDataAdapter4.DeleteCommand.Connection.Close();
                }
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
                status = false;
            }

            if (status)
                MessageBox.Show("预选成功！");
            else
                MessageBox.Show("预选失败！请重试！");

            // 刷新所有状态
            refresh_btn_Click(null, null);
        }

        private void submit_btn_Click(object sender, EventArgs e)
        {
            bool status = true;    
            try
            {
                // 获取预选课程列表
                oleDbDataAdapter4.Fill(dataSetCourseAdded1);
                for (int i = 0; i < dataSetCourseAdded1.Tables["CourseSelected"].Rows.Count; i++)
                    if (dataSetCourseAdded1.Tables["CourseSelected"].Rows[i]["status"].ToString() == "0")
                        course_confirm_list.Add(dataSetCourseAdded1.Tables["CourseSelected"].Rows[i]["course_id"].ToString());
                // 更新预选课程为已选课程
                foreach (String course in course_confirm_list)
                {
                    DataRow new_row = dataSetCourseAdded1.Tables["CourseSelected"].NewRow();
                    new_row["student_id"] = student_id;
                    new_row["course_id"] = course;
                    new_row["status"] = 1;
                    dataSetCourseAdded1.Tables["CourseSelected"].Rows.InsertAt(new_row, 0);
                }
                // 遍历增加课程列表，并将包括的课程加入数据库的已选课程表中
                foreach (String course in course_add_list)
                {
                    DataRow new_row = dataSetCourseAdded1.Tables["CourseSelected"].NewRow();
                    new_row["student_id"] = student_id;
                    new_row["course_id"] = course;
                    new_row["status"] = 1;
                    dataSetCourseAdded1.Tables["CourseSelected"].Rows.InsertAt(new_row, 0);
                }
                oleDbDataAdapter4.Update(dataSetCourseAdded1, "CourseSelected");

                String course_delete_command;
                // 遍历删除课程列表，并将包括的课程移除出数据库的已选课程表
                foreach (String course in course_remove_list)
                {
                    course_delete_command = "delete from CourseSelected WHERE student_id = '" + student_id + "' and course_id = '" + course + "'";
                    oleDbDataAdapter4.DeleteCommand.CommandText = course_delete_command;
                    oleDbDataAdapter4.DeleteCommand.Connection.Open();
                    oleDbDataAdapter4.DeleteCommand.ExecuteNonQuery();
                    oleDbDataAdapter4.DeleteCommand.Connection.Close();
                }
                // 删除冗余信息
                course_delete_command = "delete from CourseSelected WHERE student_id = '" + student_id + "' and status = 0";
                oleDbDataAdapter4.DeleteCommand.CommandText = course_delete_command;
                oleDbDataAdapter4.DeleteCommand.Connection.Open();
                oleDbDataAdapter4.DeleteCommand.ExecuteNonQuery();
                oleDbDataAdapter4.DeleteCommand.Connection.Close();
            }
            catch(Exception exc)
            {
                MessageBox.Show(exc.Message);
                status = false;
            }

            if (status)
                MessageBox.Show("选课成功！");
            else
                MessageBox.Show("选课失败！请重试！");

            // 刷新所有状态
            refresh_btn_Click(null, null);
        }

        private void cancel_btn_Click(object sender, EventArgs e)
        {
            // 刷新所有状态
            refresh_btn_Click(null, null);
        }

        private void exit_btn_Click(object sender, EventArgs e)
        {
            // 关闭窗口
            Close();
        }
    }
}
