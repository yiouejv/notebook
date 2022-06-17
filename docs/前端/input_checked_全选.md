
```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title></title>
    </head>
    <body>
    <div>
        <input type="checkbox" class="check-all" />全选<br />
        <input type="checkbox" class="check-one" />
        <input type="checkbox" class="check-one" />
        <input type="checkbox" class="check-one" />
        <input type="checkbox" class="check-one" />
        <input type="checkbox" class="check-one" />
        <input type="checkbox" class="check-one" /><br />
        <input type="checkbox" class="check-all" />全选<br /><br /><br /><br />
    </div>
         <script type="text/javascript" src='http://libs.baidu.com/jquery/2.0.0/jquery.js'></script>    
        <script>
            $(function(){
                //check-all
                $(".check-all").click(function(){
                    if($(this).prop("checked")){
                        $(".check-one,.check-all").prop("checked",true);
                    }else{
                        $(".check-one,.check-all").prop("checked",false);
                    }
                })
                //check-one
                $(".check-one").click(function(){
                    var flag = 1; //默认全选状态
                    $(".check-one").each(function(){
                        if(!$(this).prop("checked")){
                            flag = 0;
                        }
                    })
                    if(flag){
                        $(".check-all").prop("checked",true);
                    }else{
                        $(".check-all").prop("checked",false);
                    }
                })
            })
        </script>
    </body>
</html>
```