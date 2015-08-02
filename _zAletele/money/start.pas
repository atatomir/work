var time,money,ts:integer;
    total:real;
    f:text;

begin
total:= 0;
assign(f,'file.bin');
reset(f);
readln(f,ts);
readln(f,time);
readln(f,money);
writeln(ts);
writeln(time);
writeln(money);
total:= (time/ts)*money*60 ;
write('TOTAL:');
write(round(total));
read(ts);









close(f);
end.
