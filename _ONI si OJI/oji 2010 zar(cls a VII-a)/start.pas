var f,fo:text;
    n:word;
    k,i:longint;
    f1,f2,f3,j:byte;
    tura,pos:byte;

begin

 assign(f,'zar.in'); reset(f);
 assign(fo,'zar.out'); rewrite(fo);

 readln(f,n,k);
 read(f,f1);
 read(f,f2);
 read(f,f3);

 tura:= 1;
 pos := 0;
 i:= 1;

 repeat

   inc(pos);

   if pos = n then
  begin
    pos:= 1;
    inc(tura);
  end;


  if tura = 5 then
    tura := 1;

  case tura of
   1:begin
       j := f3;
       f3 := f2;
       f2 := 7 - j;
     end;
   2:begin
       j:= f1;
       f1 := f2;
       f2:= 7 - j;
     end;
   3:begin
        j:= f2;
        f2:= f3;
        f3:= 7 - j;
     end;
   4:begin
       j := f2;
       f2:= f1;
       f1:= 7 -j;
     end;
 end;



  inc(i);
 until i = k+1;

 writeln(fo,'Fetele sunt : ',f1, ',' , f2 ,',' , f3);











 close(fo);
 close(f);
end.
