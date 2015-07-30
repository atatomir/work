uses sysutils;

var f,fo:text;
    n,i,j,pr,ultima:byte;
    l:word;
    bun:boolean;
    p1,p2:word;
    //t1,t2:double;

begin
  //t1:=time;
  assign(f,'paranteze.in'); reset(f);
  assign(fo,'paranteze.out'); rewrite(fo);

  readln(f,n);

  for i := 1 to n do
  begin
    ultima := 10;
    p1 := 0; p2 := 0 ;
    bun := true;
    read(f,l);
    for j := 1 to l do
    begin
      read(f,pr);
      case pr of
        0: inc(p1);
        1: dec(p1);
        2: inc(p2);
        3: dec(p2);
      end;
      //writeln(pr,' ',ultima);
      if ((ultima = 0) and (pr=3)) or ((ultima = 2) and (pr=1)) then
      begin
        writeln(fo,'Nu');
        //writeln('NU');
        bun := false;
        break;
      end
      else
        ultima := pr;
    end;
    if (bun = true) and (p1=0) and (p2=0) then
    begin
      writeln(fo,'Da');
      //writeln('DA');
    end
    else
      if (bun=true) and (p1<>0) then
        writeln(fo,'Nu');
    readln(f);
  end;






  close(f);
  close(fo);
  //t2:= time;
  //write((t2-t1)*24*3600*1000000);
end.
