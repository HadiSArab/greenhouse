<?php
    include("connection.php");
	echo $id=$_POST['id'];
	echo $sts=$_POST['sts'];
	global $dbc;
	$q=mysqli_query($dbc,"UPDATE `device_details` SET `status`='".$sts."' WHERE `id`='".$id."'")or die("Unable to Update the Device Status");
	if($q){
		echo "Device".$id." Status=".$sts." Updated Success fully";
	}else{
		echo "Unable to update device Status";
	}
?>