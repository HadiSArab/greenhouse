<?php
	$servername = "localhost";
	$username = "root";
	$password = "";
	// Create connection
	global $dbc;
	$dbc = new mysqli($servername, $username, $password);

	// Check connection
	if ($dbc->connect_error) {
	    echo $page = $_SERVER['PHP_SELF'];
	    $sec = "0";
	    header("Refresh: $sec; url=$page");
	    die("Connection failed: " . $conn->connect_error);
	    
	}
	nl2br("\n");
	$db=mysqli_select_db($dbc,"autodb")or die("database connection failed");
	session_start();
?>


