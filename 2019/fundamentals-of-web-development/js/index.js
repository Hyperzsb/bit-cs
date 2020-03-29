var startTime;
var endTime;

function greet(){
	var time=new Date();
	var hour=time.getHours();
	$("#greetModalResponse").fadeIn();
	$("#modalResponse").hover(function(){$("#modalResponse").bind("mousewheel", function(e) { e.preventDefault(); return false; });},function(){$("#modalResponse").unbind("mousewheel");});
	$(".modalResponseDetialCloseButton").eq(0).on("click",function(){
		$("#greetModalResponse").fadeOut();
	});
	if(hour>=6&&hour<=10)
		$(".modalResponseDetialText").eq(0).text("早上好！");
	else if(hour>=11&&hour<=15)
		$(".modalResponseDetialText").eq(0).text("中午好！");
	else if(hour>=16&&hour<=19)
		$(".modalResponseDetialText").eq(0).text("下午好！");
	else
		$(".modalResponseDetialText").eq(0).text("晚上好！");
	return 0;
}

function startTest(){
	startTime=new Date();
	$("#startTestButton").fadeOut("fast");
	$("#testFormContainer").slideDown("fast");
}

function getScore(){
	var scoreList=[1,0,1,3,2,[1,1,1,1,1],[0,1,1,0,0],[0,1,1,1,0],[1,1,0,1,0],[1,1,1,0,1]];
	var questionList=$('.questionContainer');
	var ansList=[-1,-1,-1,-1,-1,[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]];
	var score=0;
	if($("#name").val()!=""&&$("#time").val()!=""){
		var formTextTitles=$(".testFormTextTitle");
		for(var i=0;i<formTextTitles.length;i++){
			if(formTextTitles.eq(i).hasClass("wrong")){
				formTextTitles.eq(i).removeClass("wrong");
				switch(i){
					case 0:
						formTextTitles.eq(i).text("姓名：");
						break;
					case 1:
						formTextTitles.eq(i).text("守望先锋游戏时长：");
						break;
				}
			}
		}
		for(var i=0;i<questionList.length-1;i++){
			var str="input[name=question"+(i+1)+"]";
			var questionOptions=questionList.eq(i).children(str);
			if(i<5)
				for(var j=0;j<4;j++){
					if(questionOptions.eq(j).is(":checked"))
						ansList[i]=j;
				}
			else
				for(var j=0;j<5;j++)
					if(questionOptions.eq(j).is(":checked"))
						ansList[i][j]=1;
		}
		for(var i=0;i<questionList.length-1;i++){
			var str="input[name=question"+(i+1)+"]"
			var questionOptions=questionList.eq(i).children(str);
			if(i<5){
				if(ansList[i]==scoreList[i]){
					questionOptions.eq(scoreList[i]).next().addClass("right");
					score++;
				}else{
					if(ansList[i]!=-1){
						questionOptions.eq(ansList[i]).next().addClass("wrong");
						questionOptions.eq(scoreList[i]).next().addClass("right");
						questionList.eq(i).next().show();
					}else{
						questionOptions.eq(scoreList[i]).next().addClass("right");
						questionList.eq(i).next().show();
					}
				}
			}else{
				var flag=false;
				for(var j=0;j<5;j++){
					if(ansList[i][j]!=scoreList[i][j]){
						flag=true;
						if(scoreList[i][j]==1)
							questionOptions.eq(j).next().addClass("right");
						else
							questionOptions.eq(j).next().addClass("wrong");
					}else{
						if(scoreList[i][j]==1)
						questionOptions.eq(j).next().addClass("right");
					}
				}
				if(flag)
					questionList.eq(i).next().show();
				else
					score++;
			}
		}
		$.ajax({
			type:"get",
			url:"addNew.asp",
			data:{name:$("#name").val(),scoreNum:score,time:$("#time").val()}, 
			success:function(data){
				endTime=new Date();
				showResultModal(score,endTime-startTime);
				if($("#historySheet>tbody").children().length>1)
					$("#historySheet>tbody").children().remove("tr[name=record]");
				var rank=1;
				$(data).find("root").find("record").each(function(index,ele){
					$("#historySheet").append(
						"<tr name=\"record\">"+
						"<td>"+(rank++)+"</td>"+
						"<td>"+$(ele).find("name").text()+"</td>"+
						"<td>"+$(ele).find("time").text()+"</td>"+
						"<td>"+$(ele).find("score").text()+"</td>"+
						"</tr>");
				});
			}
		});
		return score;
	}else{
		var formTextTitles=$(".testFormTextTitle");
		for(var i=0;i<formTextTitles.length;i++){
			if(formTextTitles.eq(i).hasClass("wrong")){
				formTextTitles.eq(i).removeClass("wrong");
				switch(i){
					case 0:
						formTextTitles.eq(i).text("姓名：");
						break;
					case 1:
						formTextTitles.eq(i).text("守望先锋游戏时长：");
						break;
				}
			}
		}
		if($("#name").val()==""){
			$(".testFormTextTitle").eq(0).text("请输入你的姓名：");
			$(".testFormTextTitle").eq(0).addClass("wrong");
		}
		if($("#time").val()==""){
			$(".testFormTextTitle").eq(1).text("请输入你的游戏时间：");
			$(".testFormTextTitle").eq(1).addClass("wrong");
		}
	}
}

function getHistory(){
	if($("#historyButton").hasClass("testFormButtonChecked")){
		$("#historyContainer").slideUp("fast");
		$("#historyButton").text("查看提交历史");
		$("#historyButton").removeClass("testFormButtonChecked");
		return 0;
	}else{
		if($("#historySheet>tbody").children().length>1){
			$("#historyButton").text("收起");
			$("#historyButton").addClass("testFormButtonChecked");
			$("#historyContainer").slideDown("fast");
			return 0;
		}
		else{
			$.ajax({
				url:"getHistory.asp",
				dataType:"xml",
				success:function(data){
					if($("#historySheet>tbody").children().length>1)
						$("#historySheet>tbody").children().remove("tr[name=record]");
					var rank=1;
					$(data).find("root").find("record").each(function(index,ele){
						$("#historySheet").append(
							"<tr name=\"record\">"+
							"<td>"+(rank++)+"</td>"+
							"<td>"+$(ele).find("name").text()+"</td>"+
							"<td>"+$(ele).find("time").text()+"</td>"+
							"<td>"+$(ele).find("score").text()+"</td>"+
							"</tr>");
					});
				}
			});
			$("#historyButton").text("收起");
			$("#historyButton").addClass("testFormButtonChecked");
			$("#historyContainer").slideDown("fast");
			return 1;
		}
	}
}

function showResultModal(score,time){
	$("#modalResponse").fadeIn();
	$("#modalResponse").hover(function(){$("#modalResponse").bind("mousewheel", function(e) { e.preventDefault(); return false; });},function(){$("#modalResponse").unbind("mousewheel");});
	//$(document).bind('mousewheel', function(event, delta) {return false;});
	$(".modalResponseDetialCloseButton").eq(1).on("click",function(){
		$("#modalResponse").fadeOut();
		//$(document).unbind('mousewheel');
	});
	$(".modalResponseDetialText").eq(3).text("你的分数是："+score+"！");
	$(".modalResponseDetialText").eq(4).text("你的用时是："+time/1000+"秒！");
	return 0;
}

function resetTest(){
	var questionList=$('.questionContainer');
	for(var i=0;i<questionList.length-1;i++){
		var str="input[name=question"+(i+1)+"]";
		var questionOptions=questionList.eq(i).children(str);
		for(var j=0;j<questionOptions.length;j++){
			questionOptions.eq(j).prop("checked",false);
			questionOptions.eq(j).next().removeClass("right");
			questionOptions.eq(j).next().removeClass("wrong");
		}
		questionList.eq(i).next().hide();
	}
	var formTextTitles=$(".testFormTextTitle");
	var formTexts=$(".testFormText");
	for(var i=0;i<formTextTitles.length;i++){
		formTexts.eq(i).val("");
		if(formTextTitles.eq(i).hasClass("wrong")){
			formTextTitles.eq(i).removeClass("wrong");
			switch(i){
				case 0:
					formTextTitles.eq(i).text("姓名：");
					break;
				case 1:
					formTextTitles.eq(i).text("守望先锋游戏时长：");
			}
		}
	}
	return 0;
}

function hobbyChange(index){
	var hobbyButtons=$('.hobbyNavDiv');
	var hobbyPages=$('.hobbyDetial');
	for(var i=0;i<hobbyPages.length;i++){
		if(hobbyButtons.eq(i).hasClass("hobbyNavDivChecked")){
			if(i!=index)
				hobbyButtons.eq(i).removeClass("hobbyNavDivChecked");
			else
				return ;
		}
		hobbyPages.eq(i).fadeOut();
	}
	for(var i=0;i<hobbyPages.length;i++)
		if(i==index){
			hobbyButtons.eq(i).addClass("hobbyNavDivChecked");
			hobbyPages.eq(i).fadeIn();
			break;
		}
	return index;
}

function navGotoSelfDescription(){
    window.location.hash="#selfDescription";
	location.hash=null;
}
function navGotoHobby(){
	window.location.hash="#hobby";
	location.hash=null;
}
function navGotoAbout(){
    window.location.hash="#test";
	location.hash=null;
}