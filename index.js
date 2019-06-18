var ipc = require('electron').ipcRenderer;
var fs = require("fs");

bt_anim("#closebt","img/closehvr.png");//add close button anime

txt_anim(".idx", " rgba(0, 0, 0,0.9)");//add txt button anime


lb_anim(".idx", "rgb(224, 229, 241)",function(id){//add left bar task
    switch(id){
        case "homeidx": 
            showpage(".page","#homepg");
            break;
        case "cfgidx": 
            showpage(".page","#cfgpg");
            break;
        case "fdidx": 
            showpage(".page","#fdpg");
            break;
        case "wtridx": 
            showpage(".page","#wtrdpg");
            break;
        case "wgtidx": 
            showpage(".page","#wgtpg");
    }
});

//add close function
$("#closebt").click(function (){1
    ipc.send('window-close');
});

$('#homeidx').trigger("click");

updatemessage("New Message");

$("#homepg").on("pageshown",function(){
  
    $("#mp").css({animation:"rot 1.5s"});
    $("#slp").css({animation:"rot 1s"});
    $("#srp").css({animation:"rot 1.25s"});
});


//config
let weight=20;
let food=50;
//save button anime
$("#svbt").hover(function(){

    $(this).css({background:"rgb(243, 246, 255)"});
},function(){
    $(this).css({background:""});
});

$("#svbt").click(function(){
    ipc.send('save',{weight:weight,food:food});
});

$(".ico").hover(function(){
    $(this).css({color:"rgb(143, 180, 249)"});
},function(){
    $(this).css({color:""});
});

$("#cfg1btn .up").click(function(){
 
    if(weight===null) return;
    if(weight == 15) return;   
    weight+=1;
    $("#cfg1set .valuect p").html(weight);
})

$("#cfg1btn .down").click(function(){
    if(weight===null) return;
    if(weight == 0) return;
    weight-=1;
    $("#cfg1set .valuect p").html(weight);
})

$("#cfg2btn .up").click(function(){
    if(food===null) return;
    if(food == 100) return;
    food+=50;
    $("#cfg2set .valuect p").html(food);
})

$("#cfg2btn .down").click(function(){
    if(food===null) return;
    if(food == 0) return;
    food-=5;
    $("#cfg2set .valuect p").html(food);
})

//food chart
buildchart('fdChart',"food.json","Food Intake(g)","g",'7 Days Food Intake','rgba(255, 99, 132, 1)','rgba(255, 99, 132, 0.2)');
buildchart('wtChart',"water.json","water Intake(g)","g",'7 Days Water Intake','rgba(54, 162, 235, 1)','rgba(54, 162, 235, 0.2)');
buildchart('wgChart',"weight.json","Weight(kg)","Kg",'7 Days Weight','rgba(255, 206, 86, 1)','rgba(255, 206, 86, 0.2)');