<?php
    include("connection.php");
	$email=$_POST['email'];
	$pass=$_POST['pass'];
	$db_pass=0;
	global $dbc;
	$q=mysqli_query($dbc,"select * from user where `email`='".$email."'") or die("Unable to get email information..");
	$num=mysqli_num_rows($q);
	if($num>0){
		while($f=mysqli_fetch_assoc($q)){
			$db_pass=$f['pass'];
		}
		if($pass==$db_pass){
			$_SESSION['user_name']=md5($email);
			echo "success";
		}else{
			echo "Password Does Not Matched...";
		}
	}else{
		echo "Email Id Not Registered, Please enter a registered email id and try again";
	}
?>