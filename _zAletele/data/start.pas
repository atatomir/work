uses sysutils,crt;
var a:boolean;
    yy,mm,dd:word;



begin
  a:=true;
  repeat
    decodedate(date,yy,mm,dd);
    writeln(dd,'.',mm,'.',yy,' ',timetostr(time));
    delay(1000);
    clrscr;
  until a=false;
end.
