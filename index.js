var ipc = require('electron').ipcRenderer;


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