const m=1000000007;
var t,ti,h,i:longint;
    n,k,r,rt:int64;
    val:array[0..1000005]of int64;
    bufin,bufout:array[1..65000]of byte;

begin
  assign(input,'cabana.in'); reset(input);
  assign(output,'cabana.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(t);
  for i := 2 to 1000000 do val[i] := (val[i-1] * i)mod m;
  for ti := 1 to t do
  begin
    readln(n,k);  val[1] := 1;
    r := val[k]; rt := 1;
    h := n div k;
    for i := 2 to h do r := (r*r) mod m;
    h := k - (n mod k) +1;
    for i := k downto h do rt := (rt * i) mod m;
    r := (r*rt) mod m;

    writeln(r);
  end;



  close(input);
  close(output);
end.