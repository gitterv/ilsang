<?php
    /*
     * @AUTHOR : 주민범
     * @DATE : 2018. 06. 26. TUE
     * @DESCRIPTION : 수임 1455번 제증명서류 발급 신청서 환경 개선 건 개발을 위한 메인 페이지 생성
    */
	// 로그인 쿠키 확인
	if(is_null($_COOKIE["employee_cookey"])) {
		$employee_cookey = "";
	} else {
		$employee_cookey = $_COOKIE["employee_cookey"];
	}
	if($employee_cookey =="" or $employee_cookey =="0") {
		exit;
	}



  include_once ('./SSI/DB.htm');
  //include_once ("https://youiwe.user.to/split.asp");
  include_once  ('./SSI/string_check.htm');
	// 로컬 접속
	$DbConn = new DbConn();
	$getLocal_giadmin = $DbConn->getLocal_giadmin();

  // Set environmental variables
  $PAGENATION['current_page'] = IsNullOrEmptyString($_GET['page'])? 1:(int)$_GET['page'];
  $PAGENATION['item_amount_per_page'] = IsNullOrEmptyString($_GET['item_amount_per_page'])? 30:(int)$_GET['item_amount_per_page'];

  	// 로컬 접속
	$DbConn = new DbConn();
	$getLocal_giadmin = $DbConn->getLocal_giadmin();

	// 로그인 정보
		$employeeinfo_sql = "select e.employeeNo, e.employeeName, e.departmentNo, d.departmentName, e.positionNo, p.positionName, p.positionAuthority from report_employeeInfo e ";
		$employeeinfo_sql = $employeeinfo_sql." join report_department d on e.departmentNo=d.departmentNo ";
		$employeeinfo_sql = $employeeinfo_sql." join report_position p on e.positionNo = p.positionNo  ";
		$employeeinfo_sql = $employeeinfo_sql." WHERE e.employeeNo = '".$_COOKIE["employee_cookey"]."' ";
		//$employeeinfo_sql = $employeeinfo_sql." WHERE e.employeeName = '신용우'";
		$employee_info = mysql_query($employeeinfo_sql, $getLocal_giadmin) ;

		if(mysql_num_rows($employee_info) >= 1) {
			$employee_result = mysql_fetch_array($employee_info);
			$employeeNo = $employee_result["employeeNo"];
			$positionName = $employee_result["positionName"];
			$departmentName = $employee_result["departmentName"];
			$employeeName  = $employee_result["employeeName"];
			$cdepartmentNo  = $employee_result["departmentNo"];
			$signNo  = $employee_result["positionNo"];
			}
?>

<html>
<head>
  <title>관리자 화면 - 사내 신청서</title>
	<meta http-equiv="Content-Type" content="text/html; charset=euc-kr">
	 <link href="css/cstyle.css" rel="stylesheet" type="text/css">
 <!-- <script src="http://apps.bdimg.com/libs/jquery/1.10.2/jquery.min.js"></script> -->
 <!-- <script src="http://apps.bdimg.com/libs/jqueryui/1.10.4/jquery-ui.min.js"></script> -->
  <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/2.0.0/jquery.min.js"></script>
  <script src="http://code.jquery.com/jquery-1.11.0.min.js"></script>
  <script type="text/javascript" src="http://youiwe.user.to/js/func.js?ver=1"></script>
  <!--<script type="text/javascript" src="http://youiwe.user.to/js/calendar.js"></script> -->
  <script type="text/javascript" src="js/func.js"></script>
  <script type="text/javascript" src="js/calendar.js"></script>
  <script>
//---------------------------------------------------------------------------------------------
// 2020.08.31 통큰실 실장 권영문
// 메모 : sessionstorage사용시 윈도우전역에 영향을 끼치게됨에 따라 컨트롤제한설정추가방법을 고안필요하지만 시간이 소요됨에 따라
//          코드분석결과, sessionstorage를 사용하지않아도 됨을 확인후 코드주석처리
//  	var name="";
	// 가져올 때
//	name = sessionStorage.getItem('saved_name')

//	function sign_kind_all(){
//		name = "all";
//		sessionStorage.setItem('saved_name', name);
		//alert(name);
//		search.action = "index.htm?name=all";
//		search.submit();
//	}

//	function sign_kind(){
//		name = "sign";
//		sessionStorage.setItem('saved_name', name);
		//alert(name);
//		search.action = "index.htm?name=sign";
//		search.submit();
//	}

//	function sign_kind_no(){
//		name = "nosign";
//		sessionStorage.setItem('saved_name', name);
		//alert(name);
//		search.action = "index.htm?name=nosign";
//---------------------------------------------------------------------------------------------		
	function change_view(name){
		search.action = "index.htm?name="+name;
		search.submit();
	}

  	function showDetail_modify(num){
		var url = "./pop_up/edit_vacation.htm?num=" + num;
		window.open(url,"/pop_up/edit_vacation", "width=790px, height=950px, left=10, top=10, scrollbars=yes, overflow:scroll");
	}

		//미결제내역출력
	function select_uncomplet(str){
		document.getElementById("current_page").value = "1";
		document.getElementById("index_num").value = "1";

		//비슷한 기능인 결제전 기능에 대한 옵션을 무력화 시킨다
		try{
			document.getElementById("sign_report").checked = true;
			document.getElementById("sign_report_area1").style.display = "none";
			document.getElementById("sign_report_area2").style.display = "none";
			document.getElementById("sign_report_area3").style.display = "none";
		}
		catch (e){ //매니져 수습사원이라서 없는경우
		}
		//기능 - 미결제, 미지출, 전체(30일)조회 / sign, pay, (공백)
		document.getElementById("page_kind").value = str ;

		//아래검색기능 초기화
		for(var i=0;i<document.post_report.search_type.length;i++){
			document.post_report.search_type[i].checked=false;
		}
		document.getElementById("search_text").value= "";
		document.getElementById("paydate_search_mode").checked=false;

		document.post_report.submit();
	}
	//alert(name);

</script>
</head>
<style type='text/css'>
  BODY, table, tr, td ,div { font-family:  "굴림" "돋움" "Arial","verdana" ; color:#4f4f4f; font-size: 9pt; line-height: 13pt}
  input, textarea, select { font-family:  "굴림" "돋움" "Arial", "verdana" ; color:#4f4f4f; font-size: 9pt;}

  .return_button { font-family:  "굴림" "돋움" "Arial","verdana" ; color:#4f4f4f; font-size: 9pt; line-height: 13pt;}
  .main_title {font-size:18px;font-weight:bold; }

  A:link {color:#2e4956;text-decoration:none;}
  A:visited {color:#2e4956;text-decoration:none;}
  A:active {color:#ff6600;text-decoration:none;}
  A:hover {color:#ff6600;text-decoration:none;}

  #center{width:100%;max-width:1440px;position:relative;margin:0 auto;}

  td#pagination form {display: inline-block}
</style>

<body>
<!--<a href="https://youiwe.user.to/split.asp"></a>-->

<div id='center'>


  <?php include('./SSI/menu.htm'); // Menu?>
  <table id='table2' width='1240'>
    <tr height="25">
      <td class="menu1">근태관련 신청서 > 휴가, 조퇴, 외출 신청서</td>
    </tr>
    <tr>
      <td class='cont3'>
        <table cellpadding='0' cellspacing='0' id='table3'>
          <tbody>
          <form name="search" id="search" method="POST" action="index.htm">
            <tr>
              <td class='sub1'>일&nbsp;&nbsp;자</td>
              <td class='sub2'>
                <input type='text' name='start_date' id='start_date'  value='<?php echo$_POST["start_date"]; //echo date("Y-m-d") ?>' style='text-align:center;'>
                <img class='cursor_hand' src='http://youiwe.user.to/admin/application_tongken/img/calendar.gif' onclick='javascript:openCalendar("start_date", event);'>
                ~
                <input type='text' name='end_date' id='end_date' value='<?php echo $_POST["end_date"]; //echo date("Y-m-d") ?>' style='text-align:center;'>
                <img class='cursor_hand' src='http://youiwe.user.to/admin/application_tongken/img/calendar.gif' onclick='javascript:openCalendar("end_date", event);'>
                &nbsp;&nbsp;
                <input type='button' value='1/4' onclick='select_date("<?php echo date('Y');?>-01-01","<?php echo date('Y');?>-03-31");' class='btn1'>
                <input type='button' value='2/4' onclick='select_date("<?php echo date('Y');?>-04-01","<?php echo date('Y');?>-06-30");' class='btn1'>
                <input type='button' value='3/4' onclick='select_date("<?php echo date('Y');?>-07-01","<?php echo date('Y');?>-09-30");' class='btn1'>
                <input type='button' value='4/4' onclick='select_date("<?php echo date('Y');?>-10-01","<?php echo date('Y');?>-12-31");' class='btn1'>
              </td>
              <td class='sub3' rowspan='2'>
<!--                <input type="hidden" name="page" value="1"/>-->
                <input type='submit' value='검색' class='btn2'/>
              </td>
            </tr>
            <tr>
              <td class='sub1'>검&nbsp;&nbsp;색</td>
              <td class='sub2'>
                <input type='text' size='18'  name='query' id='search_text' value='<?php echo $_POST["query"];?>' onfocus='this.select();'> [종류+사유+작성자]
              </td>
            </tr>
          </form>
          </tbody>
        </table>
      </td>
    </tr>
    <tr>
      <td class='cont3'>
        <table cellpadding='0' cellspacing='0' id='table3' >
          <tbody>
          <tr>
            <td class='header' onclick="help_toggle()">도움말</td>
          </tr>
          <tr>
            <td class='content' id='help_info' style='display:none;'>
              <ol style="padding-left: 10px;">
                <li>[휴가]를 선택한 경우 ‘일시’에서 선택된 일자 당 1 일을 소요한 것으로 간주합니다.</li>
                <li>[조퇴]등 시간 단위로 근태관련 신청서를 작성할 때 사유에 조퇴한 시간을 정확하게 기입하도록 합니다.</li>
                <li>조퇴가 아닌 근무 시작시간에 휴가를 사용할 경우 [기타] 를 선택하여 사유와 시간을 기입합니다.</li>
                <li>이 외에 구분에서 선택사항이 없는 경우 [기타] 를 선택하여 직접 그 사유를 기입합니다.</li>
                <li>민방위(예비군) 등 유급휴가가 인정되는 경우라도 신청서를 제출해야 합니다.</li>
                <li>모든 신청서는 기본적으로 증빙서류파일을 첨부하여 제출해야 합니다. (다만, 증빙할 서류나 자료가 없는 경우에는 사유에 그 이유를 함께 기재하도록 합니다.)</li>
                <li>근태관련 신청서는 신청내용 및 상황에 따라 거절될 수 있으며 승인되고 나서 효력이 있으므로 일정에 차질이 생기지 않도록 미리 제출합니다.</li>
              </ol>
            </td>
          </tr>
          </tbody>
        </table>
      </td>
    </tr>
    <tr>
      <td class='menu_line1'></td>
    </tr>
<?php
	// 2020.08.31 통큰실 실장 권영문
	// 메모 : 조건추가하여 초기값설정
	if ($_GET['name'] == "") {
		$sign_kind = "all";
	}else{
		$sign_kind = $_GET['name'];
	}
	//echo "*".$_SESSION['name']."*";

	if($_COOKIE["employee_cookey"] == 2 || $_COOKIE["employee_cookey"] == 3 || $cdepartmentNo == 33 || $_COOKIE["employee_cookey"] == 120 ){
		$query = "SELECT * FROM incompany_apply_vacation where ((category1 = '휴가' OR category1 = '조퇴' OR category1 = '외출' OR category1 = '기타') && (save is null || save <= 0) && (approve_belong1 > 0 || approve_belong2> 0 || approve_belong3> 0 || applier_num = ".$employeeNo." )) ";
		//echo $query;
	}else{
		if(	$_COOKIE["employee_cookey"] == 50){
			$query = "SELECT * FROM incompany_apply_vacation where ((category1 = '휴가' OR category1 = '조퇴' OR category1 = '외출' OR category1 = '기타')  and (save is null || save <= 0)  and (applier_num = $employee_cookey or applier_dep = '$departmentName'";
			$query = $query." )) ";
		}elseif($_COOKIE["employee_cookey"] == 11){
			$query = "SELECT * FROM incompany_apply_vacation where ((category1 = '휴가' OR category1 = '조퇴' OR category1 = '외출' OR category1 = '기타')  and (save is null || save <= 0)  and (applier_num = $employee_cookey or applier_dep = '$departmentName' ";
			$query = $query." or  applier_dep = 'IDC실' or applier_dep = 'IDC팀' or applier_dep = '점검팀')) ";
		}
		else {
			$query = "SELECT * FROM incompany_apply_vacation where ((category1 = '휴가' OR category1 = '조퇴' OR category1 = '외출' OR category1 = '기타')  and (save is null || save <= 0)  and (applier_num = $employee_cookey or applier_dep = '$departmentName'";
		}
		if($signNo == 5 || $signNo == 6){
			$query = $query."&& applier_res = '매니저' || applier_res = '수습사원'))";
		}elseif($signNo ==4){
			$query = $query."&& applier_res = '매니저' || applier_res = '팀장' || applier_res = '수습사원'))";
		}else{
			if($_COOKIE["employee_cookey"] == 11){
				$query = $query."";
			}
			else {
				$query = $query."))";
			}
		}
	}

	//전체 주석처리해둠
/*	if($sign_kind == "all"){
		$query = $query."";
	}
*/
	if($sign_kind == "sign"){
		$query = $query." AND approve_confirm3 > 0 ";
	}elseif($sign_kind == "nosign"){
		$query = $query." AND (approve_confirm3 <= 0 OR approve_confirm3 IS NULL)";
	}else{
		//echo "ff";
		$query = $query." ";
	}
?>
    <tr>
      <td width="50%">
<!--
// 2020.08.31 통큰실 실장 권영문
// 메모 : 함수변경
-->
		<input type='button' value='전체' onclick="change_view('all')" style="width:60px; height:30px; float:left; cursor:pointer;
<?php
	if($sign_kind == 'all'){
?>
		border:1px solid #596f19; color:#ffffff ; background-color:#596f19;">
<?php
	}else{
?>
		border:1px solid #596f19; color:#596f19 ; background-color:#ffffff;">
<?php
	}
?>
        <!--<input type='button' value='승인' onclick="sign_kind()" style="width:60px; height:30px; float:left; cursor:pointer;
<?php
	if($sign_kind == "sign"){
?>
		border:1px solid #596f19; color:#ffffff ; background-color:#596f19;">
<?php
	}else{
?>
		border:1px solid #596f19; color:#596f19 ; background-color:#ffffff;">
<?php
	}
?>
-->
<!--
// 2020.08.31 통큰실 실장 권영문
// 메모 : 함수변경
-->
	<input type='button' value='미결재' onclick='change_view("nosign")' style="width:60px; height:30px; float:left; cursor:pointer; margin-left:5px;
<?php
	if($sign_kind == 'nosign'){
?>
border:1px solid #596f19; color:#ffffff ; background-color:#596f19;">
<?php
	}else{
?>
		border:1px solid #596f19; color:#596f19 ; background-color:#ffffff;">
<?php
	}
?>
	<form method="post" action="pop_up/write_vacation.htm" target="editor" onsubmit="create_new_window('editor');">
        <input type="hidden" value="<?php echo $_COOKIE['employee_cookey'];?>" name="employee_idx"/>
        <input type='submit' value='작성' onclick='' class='btn1' style="width:70px; height:30px; float:right; border:1px solid #596f19; color:#596f19 ; background-color:#ffffff;">
    </form>
      </td>
    </tr>
    <tr>
      <td class='menu_line1'></td>
    </tr>
    <tr>
      <td>
        <table cellpadding=0 cellspacing=0 border=0 width="1240" align='center' id='table4'>
		<colgroup>
			<col width=10%>
			<col width=15%>
			<col width=15%>
			<col width=20%>
			<col width=15%>
			<col width=15%>
			<col width=10%>
		</colgroup>

          <tr>
            <!--<td height="30" align="center" class='sub4'>번호</td>-->
            <td height="30" align="center" class='sub4'>종류</td>
            <td align="center" class='sub4'>작성일자</td>
            <td align="center" class='sub4'>신청일자</td>
            <td align="center" class='sub4'>사유</td>
            <td align="center" class='sub4'>작성자</td>
            <td align="center" class='sub4'>최종결재자</td>
            <td align="center" class='sub4'>첨부파일</td>
          </tr>
<?php

	//echo $query."<br>";

	$conditional_query = '';

	$search_keyword = $_POST['query'];
	$start_date = $_POST['start_date'];
	$end_date = $_POST['end_date'];

  if (!IsNullOrEmptyString($start_date)) {
    $conditional_query = !IsNullOrEmptyString($conditional_query)? $conditional_query.' AND ':'';
    $conditional_query = $conditional_query . "and regist_date > '{$start_date} 00:00:00'";
  }

  if (!IsNullOrEmptyString($end_date)) {
    $conditional_query = !IsNullOrEmptyString($conditional_query)? $conditional_query.' AND ':'';
    $conditional_query = $conditional_query . "regist_date < '{$end_date} 23:59:59'";
  }

  if(!IsNullOrEmptyString($search_keyword)) {
    //$conditional_query = !IsNullOrEmptyString($conditional_query)? $conditional_query.' AND ':'';

    // Get user name and index
//    $temp_query = "";
//    query_mysql($temp_query);

		$einfo_query = "select employeeNo, employeeName from report_employeeInfo";
		$einfo_query = $einfo_query." WHERE employeeName = '$search_keyword'";
		$einfo_query_info = mysql_query($einfo_query, $getLocal_giadmin) ;
		$row3 = mysql_fetch_assoc($einfo_query_info);
		$eNo  = $row3["employeeNo"];

    $conditional_query = $conditional_query . " and (CONCAT_WS('+',category1,description,applier_num) LIKE  '%".$search_keyword."%' ";
	if($eNo != null){
		$conditional_query = $conditional_query . "OR applier_num LIKE  '%".$eNo."%')";
	}else{
		$conditional_query = $conditional_query .")";
	}
  }

  if(!IsNullOrEmptyString($conditional_query)) {
    $query = $query.$conditional_query;
	//$query = $query.$conditional_query;
  }

//DESCEND SORT
$query = $query.' ORDER BY regist_date DESC ';

//PAGING
$query = $query.' LIMIT '.($PAGENATION['current_page']-1)*$PAGENATION['item_amount_per_page'].','.
  ($PAGENATION['current_page'])*$PAGENATION['item_amount_per_page'];

  //Check Query
	//echo $query;

  $result = query_mysql($query);
if ($result->num_rows > 0) {
  // output data of each row
  while($row = $result->fetch_assoc()) {

  	If ($row["approve_confirm3"] > 0){
		$sign_message = "(부)사장";
	}
	ElseIf ( $row['approve_confirm2'] > 0){
		$sign_message = "발급부서 실장";
	}
	ElseIf ( $row['approve_confirm1'] > 0){
		$sign_message = "발급부서 담당";
	}
	ElseIf ( $row['approve_belong3'] > 0){
		$sign_message = "소속 부서장";
	}
	ElseIf ( $row['approve_belong2'] > 0){
		$sign_message = "소속 팀장";
	}
	ElseIf ( $row['approve_belong1'] > 0){
		$sign_message = "신청자";
	}
	Else{
		$sign_message = "작성중";
	}

		$einfo_sql = "select employeeNo, employeeName from report_employeeInfo";
		$einfo_sql = $einfo_sql." WHERE employeeNo = ".$row["applier_num"];
		$einfo_sql_info = mysql_query($einfo_sql, $getLocal_giadmin) ;
		$row2 = mysql_fetch_assoc($einfo_sql_info);
		$eName  = $row2["employeeName"];

?>
	<tr style="background-color: rgb(255, 255, 255);" onmouseover="this.style.backgroundColor='#DAEED9'" onmouseout="this.style.backgroundColor='#FFFFFF'" align='center'>
		<td align=center onclick="showDetail_modify('<?php echo $row['idx']; ?>');"><?php echo $row['category1'];?></td>
		<td align=center onclick="showDetail_modify('<?php echo $row['idx']; ?>');"><?php echo substr($row['regist_date'], 0, 10);?></td>
		<td align=center onclick="showDetail_modify('<?php echo $row['idx']; ?>');"><?php echo $row['apply_start_date'];?></td>
		<td align=center onclick="showDetail_modify('<?php echo $row['idx']; ?>');"><?php 
							if (strlen(explode(chr(13).chr(10),$row['description'] )[0]) > 30){
								$description_content = mb_substr(explode(chr(13).chr(10),$row['description'])[0],0,30,'euc-kr')."...";
							} else {
								//$description_content = explode(chr(13).chr(10),$row['description'])[0];
								$description_content = explode(chr(13).chr(10),$row['description'])[0];
							}
							echo $description_content;
		?></td>
		<td align=center onclick="showDetail_modify('<?php echo $row['idx']; ?>');"><?php echo $eName;?></td>
		<td align=center onclick="showDetail_modify('<?php echo $row['idx']; ?>');"><?php echo $sign_message;?></td>
		<td align=center onclick="showDetail_modify('<?php echo $row['idx']; ?>');"><?php echo $row['attachment_path'];?></td>
	</tr>
    <tr>
		<td class='menu_line1'></td></tr>
<?php
  }
} else {
  echo "<tr onmouseover='this.bgColor=\"#F0F0F0\"' onmouseout='this.bgColor=\"#FFFFFF\"' align='center'>".
    "<td align=center colspan='100'>" . '검색결과가 없습니다.'.  "</td>".
    "<tr><td class='menu_line1'></td></tr>";
}

?>

          <?php // Pagination ?>
          <table cellpadding="0" cellspacing="0" border="0" width="1240" style="border: 1px solid #D0D0D0; background-color: #F0F0F0;">
            <tbody>
            <tr>
              <td width="100px;" style="text-align: left; padding: 3px 10px 0px 10px; background-color:white; border:0px;"><b>총 갯수 :
<?php
	if($_COOKIE["employee_cookey"] == 2 || $_COOKIE["employee_cookey"] == 3 || $_COOKIE["employee_cookey"] == 61 || $_COOKIE["employee_cookey"] == 120){
		 $whole_item_query = "SELECT COUNT(*) as TEMP_SIZE FROM mjadmin.incompany_apply_vacation where ((category1 = '휴가' OR category1 = '조퇴' OR category1 = '외출' OR category1 = '기타') && (save is null || save <= 0) && (applier_dep like '%경영관리팀%' || (applier_dep != '경영관리팀' && approve_belong3 > 0))) ".((IsNullOrEmptyString($conditional_query))? '':' and true '.$conditional_query);
	}else{
		if(	$_COOKIE["employee_cookey"] == 50 ){
			$whole_item_query = "SELECT COUNT(*) as TEMP_SIZE FROM incompany_apply_vacation where ((category1 = '휴가' OR category1 = '조퇴' OR category1 = '외출' OR category1 = '기타') and (save is null || save <= 0) and (applier_num = $employee_cookey or applier_dep = '$departmentName'".((IsNullOrEmptyString($conditional_query))? '':'true' .$conditional_query);
			$whole_item_query = $whole_item_query." )) ";
		}elseif($_COOKIE["employee_cookey"] == 11 ){
			$whole_item_query = "SELECT COUNT(*) as TEMP_SIZE FROM incompany_apply_vacation where ((category1 = '휴가' OR category1 = '조퇴' OR category1 = '외출' OR category1 = '기타') and (save is null || save <= 0) and (applier_num = $employee_cookey or applier_dep = '$departmentName'".((IsNullOrEmptyString($conditional_query))? '':'true' .$conditional_query);
			$whole_item_query = $whole_item_query." or  applier_dep = 'IDC실' or applier_dep = 'IDC팀' or applier_dep = '점검팀')) ";
		}
		else {
			$whole_item_query = "SELECT COUNT(*) as TEMP_SIZE FROM incompany_apply_vacation where ((category1 = '휴가' OR category1 = '조퇴' OR category1 = '외출' OR category1 = '기타') and (save is null || save <= 0) and (applier_num = $employee_cookey or applier_dep = '$departmentName'".((IsNullOrEmptyString($conditional_query))? '':'true' .$conditional_query);
			$whole_item_query = $whole_item_query." )) ";
		}
	}

	//전체 주석처리해둠
	if($sign_kind == "all"){
		$whole_item_query = $whole_item_query."";
/*
	}
	if($sign_kind == "sign"){
		$whole_item_query = $whole_item_query." AND approve_confirm3 > 0 ";
*/
	}elseif($sign_kind == "nosign"){
		$whole_item_query = $whole_item_query." AND (approve_confirm3 <= 0 OR approve_confirm3 IS NULL)";
	}else{
		//echo "ff";
		$whole_item_query = $whole_item_query." ";
	}
  $whole_item_result = mysql_query($whole_item_query, $getLocal_giadmin) ;
  $whole_item_row = mysql_fetch_array($whole_item_result);
  //echo mysql_num_rows($whole_item_result);
  $PAGENATION['num_rows'] = $whole_item_row['TEMP_SIZE'];
  echo $PAGENATION['num_rows'];
?>
              </b></td>
              <td id="pagination" colspan="4" style="text-align: center; background-color:white; border:0px;">
              <?php
                $page_indicator = '';
                for($k=0; $k < ($PAGENATION["num_rows"] / $PAGENATION['item_amount_per_page']) -1 && $k<9 ; $k++){
                  $page_indicator = $page_indicator.
                    '<form action="index.htm" method="GET">'.
                      '<input name="page" type="submit" value="'.($k+1).'" style="border:0px solid #FFFFFF;"></form> ';
                }
                $page_indicator = $page_indicator.
                  '<form action="index.htm" method="GET">'.
                    '<input name="page" type="submit" value="'.($k+1).'" style="border:0px solid #FFFFFF;"/>'.
                  "</form>";
                echo $page_indicator;
              ?>
              </td>
              <td width="100px" style="text-align: right; padding: 3px 10px 0px 10px; background-color:white; border:0px;"><b>총 페이지수 : <?php echo ceil($PAGENATION['num_rows'] / $PAGENATION['item_amount_per_page']); ?></b></td>
            </tr>
            </tbody>
          </table>
        </table>
        <br>
      </td>
    </tr>
  </table>
 <?php // echo $_COOKIE['employee_cookey']; ?>
</div>
</body>
</html>
