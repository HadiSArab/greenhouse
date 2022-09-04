<?php
class dht11{
 public $link='';
 function __construct($node_id, $temperature, $humidity, $hindex){
  $this->connect();
  $this->storeInDB($node_id, $temperature, $humidity, $hindex);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','bsalamir_root','hadisafararab') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'bsalamir_hadi_sensor') or die('Cannot select the DB');
 }
 
 function storeInDB($node_id, $temperature, $humidity, $hindex){
  $query = "insert into dht11 set node_id='".$node_id."', humidity='".$humidity."', temperature='".$temperature."', hindex='".$hindex."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['temperature'] != '' and $_GET['node_id'] != '' and  $_GET['humidity'] != '' and $_GET['hindex'] != ''){
 $dht11=new dht11($_GET['temperature'],$_GET['node_id'],$_GET['humidity'],$_GET['hindex']);
}
?>
