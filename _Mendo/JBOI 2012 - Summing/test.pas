var f1,f2:text;i:integer;a,b:string;

begin

 assign(f1,'summ.out');reset(f1);
 assign(f2,'bun.out');reset(f2);

 i := 1;
 while i<=887 do begin
   readln(f1,a);
   readln(f2,b);
   if a<>b then writeln(i,' ',a,' ',b);
   inc(i);
 end;

 close(f1);
 close(f2);
end.

