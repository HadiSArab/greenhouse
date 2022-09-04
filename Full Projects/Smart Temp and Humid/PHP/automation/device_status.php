<?php
    include("connection.php");
	if(isset($_GET['did'])){
		$device_id=$_GET['did'];
		global $dbc;
		$q=mysqli_query($dbc,"select `status` from `device_details` where `id`='".$device_id."'")or die("Unable to Show Result");
		while($f=mysqli_fetch_assoc($q)){
			echo $f['status'];
		}
	}
?>