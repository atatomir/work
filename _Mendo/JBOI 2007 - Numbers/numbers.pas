const l:array[1..12]of longint =(31,28,31,30,31,30,31,31,30,31,30,31);
var ti,i:longint;
    s:string;
    zi,luna,an,auth,code,ver:longint;
    ok:boolean;

function get(x:char):longint;
begin
  get := ord(x) - $30;
end;

function bisect(x:longint):boolean;
begin
  if x < 600 then x := x + 2000 else x := x + 1000;

  if x mod 100 = 0 then
    bisect := (x mod 400 = 0)
  else
    bisect := (x mod 4 = 0);
end;

begin
  for ti := 1 to 3 do
  begin

    readln(s);
    zi := get(s[1])*10+get(s[2]);
    luna := get(s[3])*10+get(s[4]);
    an := get(s[5])*100+get(s[6])*10+get(s[7]);
    auth := get(s[8]);
    code := get(s[9]);

    ver := 0;
    for i := 1 to 8 do  ver := (ver + get(s[i])*get(s[i]))mod 7;

    ok := true;
    if ver = code then
    begin
      if an < 1000 then
      begin
        if (luna > 0)and(luna < 13) then
        begin
          if zi > 0 then
          begin
            if not((zi <= l[luna])or((luna=2)and(zi=29)and bisect(an))) then ok := false;
          end
          else
            ok := false;
        end
        else
          ok := false;
      end
      else
        ok := false;
    end
    else
      ok := false;

    if ok then writeln(1) else writeln(0);

    //writeln(zi,' ',luna,' ',an,' ',auth,' ',code,' ',ver);

  end;
end.