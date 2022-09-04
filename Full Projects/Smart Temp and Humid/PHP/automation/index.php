<?php
    include("connection.php");
?>
<html>
<head>
	<title>MyHome Automation</title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
	<link rel="stylesheet" href="css/bootstrap.min.css">
	<link rel="stylesheet" href="css/w3.css">
	<link rel="stylesheet" href="css/main.css">
	<link rel="icon" href="img/2.png" type="image/gif" sizes="16x16">
	<script src="js/jquery-3.1.1.min.js"></script>
	<script src="js/bootstrap.min.js"></script>
	<script src="js/main.js"></script>
</head>
<body style="background: url(img/bg.jpg) no-repeat center center fixed; 
  -webkit-background-size: cover;
  -moz-background-size: cover;
  -o-background-size: cover;
  background-size: cover;">
    <div class="container-fluid">
	    <div class="row" style="margin:0px">
		    <div class="w3-container w3-padding w3-hide-small">
			   <h2>
				    <span class="w3-orange w3-padding margin-0">M</span>
				    <span class="w3-yellow w3-padding margin-0">y</span>
					<span class="w3-black  w3-padding margin-0">H</span>
					<span class="w3-blue   w3-padding margin-0">o</span>
					<span class="w3-pink   w3-padding margin-0">m</span>
					<span class="w3-green  w3-padding margin-0">e</span>
					<?php
					    if(isset($_SESSION['user_name'])){
					?>
					<div class="dropdown w3-right">
					  <button class="dropdown-toggle" type="button" data-toggle="dropdown"><img src="img/setting_icon.png" class="w3-right" height="20px;"></button>
					  <ul class="dropdown-menu" style="margin-left:-100px;">
						<li><a href="logout.php">LOGOUT</a></li>
					  </ul>
					</div>
					<?php
						}
					?>
				</h2>
				<br/>
				<span class="w3-text-white" >Made by techZeero.com</span>
			</div>
			<div class="w3-container w3-padding w3-hide-large w3-hide-medium">
			   <h4>
				    <span class="w3-orange w3-padding margin-0">M</span>
				    <span class="w3-yellow w3-padding margin-0">y</span>
					<span class="w3-black  w3-padding margin-0">H</span>
					<span class="w3-blue   w3-padding margin-0">o</span>
					<span class="w3-pink   w3-padding margin-0">m</span>
					<span class="w3-green  w3-padding margin-0">e</span>
					<?php
					    if(isset($_SESSION['user_name'])){
					?>
					<div class="dropdown w3-right">
					  <button class="dropdown-toggle" type="button" data-toggle="dropdown"><img src="img/setting_icon.png" class="w3-right" height="20px;"></button>
					  <ul class="dropdown-menu" style="margin-left:-100px;">
						<li><a href="logout.php">LOGOUT</a></li>
					  </ul>
					</div>
					<?php
						}
					?>
				</h4>
				<br/>
				<span class="w3-text-white">Made by techZeero.com</span>
			</div>
	    <div>
		<div class="row">
		    <div class="container">
			<?php
			    if(isset($_SESSION['user_name'])){
			?>
			    <table class="w3-table-all w3-round" id="status_table">
				    <tr>
					   <!--<th>Sl. No.</th>--><th>Device Name</th><th>On/Off</th>
					</tr>
					<?php
					    global $dbc;
			            $q=mysqli_query($dbc,"select * from `device_details`")or die("Unble to select device details");
					    while($f=mysqli_fetch_assoc($q)){
							?>
							<tr>
							   <!--<td><?php echo $f['id'];?></td> -->
							   <td><?php echo $f['type'];?></td>
							   <td>
							       <label class="switch">
									  <input type="checkbox" class="slider_switch" value="<?php echo $f['id'];?>" <?php if($f['status']==1){ echo "checked";}?>/>
									  <span class="slider round"></span>
									</label>
							   </td>
							</tr>
							<?php
						}
					?>
				</table>
			<?php
				}else{
					echo '<span class="w3-display-middle"><center><h4 class="w3-text-red"><b>Please Click on Login Button...<b></h4>
				        <br/><button class="w3-button w3-round w3-green w3-hover-pink" id="login_modal_btn">LOGIN</button></center></span>	
					';
				}
			?>	
			</div>
		</div>
	</div>
	<div class="w3-modal" id="loading_modal">
	    <center><img src="img/loading.gif" height="100px;"/>
	</div>
	<div class="w3-modal" id="login_modal">
	    <div class="w3-card-4 w3-modal-content">
		    <header class="w3-container w3-blue w3-padding">
			    <h5>LOGIN<span class="w3-right" onclick="document.getElementById('login_modal').style.display='none'">&times;</span></h5>
			</header>
			<div class="w3-container w3-padding">
			    <label>Email:</label><span id="email_res" class="w3-text-red"></span>
				<input type="email" id="user_email" placeholder="Enter Your Email..." class="w3-input"/>
				<label>Password:</label><span id="pass_res" class="w3-text-red"></span>
				<input type="password" id="user_pass" placeholder="Enter Your Password..." class="w3-input"/>
				<br/>
				<center><button class="w3-button w3-green w3-hover-pink w3-round" id="login_submit_btn">LOGIN</button></center>
			</div>
			<footer class="w3-container w3-blue w3-padding">
			    <center>
				   <span id="login_res">
				    <span class="w3-orange w3-padding margin-0">M</span>
				    <span class="w3-yellow w3-padding margin-0">y</span>
					<span class="w3-black  w3-padding margin-0">H</span>
					<span class="w3-blue   w3-padding margin-0">o</span>
					<span class="w3-pink   w3-padding margin-0">m</span>
					<span class="w3-green  w3-padding margin-0">e</span>
				   </span>	
				</center>
			</footer>
		</div>
	</div>
</body>
</html>