const uc:array[0..99]of integer=
        (
        0,1,5,2,8,3,9,2,8,7,
        7,8,4,7,3,8,4,1,5,4,
        4,5,9,6,2,7,3,6,2,1,
        1,2,8,1,7,2,8,5,9,8,
        8,9,3,0,6,1,7,0,6,5,
        5,6,2,5,1,6,2,9,3,2,
        2,3,7,4,0,5,1,4,0,9,
        9,0,6,9,5,0,6,3,7,6,
        6,7,1,8,4,9,5,8,4,3,
        3,4,0,3,9,4,0,7,1,0);
var   f,fo:text;
      s:string;
      n,l,t,i,suma:integer;
      bufin,bufout:array[1..65000]of byte;

begin
  assign(f,'cifra.in');reset(f);
  assign(fo,'cifra.out');rewrite(fo);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(f,t);

  for i := 1 to t do
  begin
    readln(f,s);
    l:=length(s);
    if l>1 then
    begin
      n:= (ord(s[l-1])-$30)*10 + (ord(s[l])-$30);
      suma:= uc[n];
      writeln(fo,suma);
    end
    else
    begin
      n := (ord(s[1])-$30);
      suma := uc[n];
      writeln(fo,suma);
    end;

  end;


  close(f);
  close(fo);
end.
