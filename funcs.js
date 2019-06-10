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

function showpage(clselector,idselector){
    //console.log(idselector);
    $(clselector).each(function(){
        $(this).css("display","none");
        
    })
    $(idselector).css("display","inline");
}

function updatemessage(message){
    $("#sttsbar").text(message);
}
