//this file contains basic functions used in index.js


function sleep(t){
    return new Promise((resolve)=>{setTimeout(()=>{resolve()},t)})
}

//add button hover animation
function bt_anim(selector, hover_img){
    $(selector).each(function(){
        let img;
        $(this).hover(function(){
            img = $(this).attr("src");
            $(this).attr("src",hover_img);
        },function(){
            $(this).attr("src",img);
        });
    });
}

let selected=null;

//add animation of text
function txt_anim(selector, color){
    $(selector).each(function(){
        let cl;
        $(this).hover(function(){
            if(selected==$(this).attr("id")) return;
            cl = $(this).css("color");
            $(this).css("color",color);
        },function(){
            $(this).css("color",cl);
        });
        $(this).click(function(){
            $(this).css("color",cl);
        })
    });
}

//add click task of left bar
function lb_anim(clslct, color, task){
    $(clslct).each(function(){ 
        $(this).click(function(){ 
            if(selected==$(this).attr("id")) return;
            selected= $(this).attr("id");
            $(clslct).css("background","").css("border-left","").css("margin-left","5px").css("color",);
            $(this).css("background",color).css("border-left","solid 5px rgb(86, 152, 206)").css("margin-left","0px");
            task($(this).attr("id"));
        });
    });
}

function fadeout(jq,time){
    return new Promise((resolve)=>{
        jq.css({opacity: 1}).animate({opacity: 0},time,"swing",function(){
            $(this).css({display:"none"});
            console.log("end");
            resolve();
        });
    });
}

function fadein(jq,time){
    return new Promise((resolve)=>{
        jq.css({opacity: 0}).animate({opacity: 1},time,"swing");
        resolve();
    });
}

let first=true;
function showpage(clselector,idselector){
    if(first){
        first=false;
        fadein($(idselector).css({display:"inline"}),200).then(()=>{
            $(idselector).trigger("pageshown");
            console.log(idselector);
        });
        return;
    }
    let outed=null;
    $(clselector).each(function(){
        if($(this).css("display")!="none") {
            outed=fadeout($(this),200);
            outed.then(()=>{
                let fd = fadein($(idselector).css({display:"inline"}),200);
                fd.then(()=>{
                    $(idselector).trigger("pageshown");
                    console.log(idselector);
                })
            });
        }
    })
    
}

function updatemessage(message){
    $("#sttsbar").text(message);
}
