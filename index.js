


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
var ipc = require('electron').ipcRenderer;
$("#closebt").click(function (){
    ipc.send('window-close');
});

$('#homeidx').trigger("click");

updatemessage("New Message");
