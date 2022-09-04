$(document).ready(function(){
   $(document).on("click",".slider_switch",function() {
		var id=$(this).val();
		if($(this).attr('checked')) {
			$.ajax({
				url:"update_device_status.php",
				type:"POST",
				data:{id:id,sts:'0'},
				beforeSend:function(){
					$("#loading_modal").css("display","block");
				},
				success:function(data){
					$("#loading_modal").css("display","none");
					$("#status_table").load(location.href + " #status_table");
					//alert(data);
				}
			});
		} else {
			$.ajax({
				url:"update_device_status.php",
				type:"POST",
				data:{id:id,sts:'1'},
				beforeSend:function(){
					$("#loading_modal").css("display","block");
				},
				success:function(data){
					$("#loading_modal").css("display","none");
					$("#status_table").load(location.href + " #status_table");
					//alert(data);
				}
			});
		}
	});
	$("#login_modal_btn").click(function(){
		$("#login_modal").css("display","block");
	});
	$("#login_submit_btn").click(function(){
		//alert("hi");
		var email=$("#user_email").val();
		var pass=$("#user_pass").val();
		var cnt=0;
		if(isEmail(email)){
			$("#user_email").css("border","1px solid green");
			$("#email_res").html("");
		}else{
			$("#user_email").css("border","1px solid red");
			$("#email_res").html("*Please Enter an Valid Email Address...");
			cnt=1;
		}
		if(pass=="" || pass==null){
			$("#user_pass").css("border","1px solid red");
			$("#pass_res").html("*Please Enter an Valid Password...");
			cnt=1;
		}else{
			$("#user_pass").css("border","1px solid green");
		}
		if(cnt==0){
			$.ajax({
				url:"login_server.php",
				type:"POST",
				data:{email:email,pass:pass},
				beforeSend:function(){
					$("#loading_modal").css("display","block");
				},
				success:function(data){
					$("#loading_modal").css("display","none");
					if(data=="success"){
					    window.location="index.php";	
					}else{
					   $("#login_res").html(data);
					}   
				}
			});
		}
	});
});
function isEmail(email) {
  var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;
  return regex.test(email);
}