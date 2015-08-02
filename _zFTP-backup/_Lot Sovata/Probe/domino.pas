type piesa= record
       a,b:byte;
     end;
var n,i,j,k1,k2,h,max,pos,t,maxi,x,y:Longint;
    v:array[0..10005]of piesa;
    bufin,bufout:array[1..65000]of byte;

function maximul(i:longint):byte;
begin
  if v[i].a >= v[i].b then
    maximul := v[i].a
  else
  if k1 > 0 then
    maximul := v[i].b
  else
    maximul := v[i].a;
end;

begin
  assign(input,'domino.in'); reset(input);
  assign(output,'domino.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n,k1,k2);

  for i := 1 to n do
  begin
    readln(x,y);
    v[i].a := x*10+y;
    v[i].b := y*10+x;
  end;

  v[n+1].a := 0; v[n+1].b := 0;

  h := n - k2; pos := 1;
  for i := 1 to h do
  begin
    max := 0;
    for j := pos to pos+k2 do
    begin
      t := maximul(j);
      if t > max then
      begin
        max := t; maxi := j;
      end;
    end;

    k2 := k2 - (maxi-pos);
    pos := maxi+1;
    if v[maxi].a <> max then dec(k1);
    write(max);

  end;




  close(input);
  close(output);
end.