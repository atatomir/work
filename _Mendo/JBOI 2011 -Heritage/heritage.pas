type line = record
       d,l:double;   // d -distanta ; l - lungime;
     end;

var n,m,i,sum,next:longint;
    v:array[0..10]of longint;
    tr:array[0..510]of line;
    arie,caut,rez,dist,lant,pos,min,ant:double;
    r,s:array[0..500]of double;
    perm,rperm:array[0..10]of longint;

function af_aria(d1,l1,d2,l2:double):double;
begin    //writeln(d1:0:2,' ',l1:0:2,' ',d2:0:2,' ',l2:0:2);
  af_aria := (d2-d1)*(l1+l2)/2;
  rez := af_aria;
end;

function ecuatie(a,b,c:double):double;
var delta:real;
begin
  if a = 0 then
  begin
    ecuatie := -c / b;
    exit;
  end;

  delta := b*b-4*a*c;
  delta := sqrt(delta);
  ecuatie := (- b + delta)/(2*a);
end;

procedure add_it(x,y:double); inline;
begin
  r[0] := r[0] + 1;
  r[trunc(r[0])] := x;
  s[trunc(r[0])] := y;
end;

procedure Permutare(pas,poz:longint;suma:double);
var i,j:longint;
    ok:boolean;
begin
  if pas = n then
  begin
    if suma < min then
    begin
      min := suma;
      for i := 1 to pas-1 do rperm[i] := perm[i];
    end;
  end
  else
  begin
    for i := 1 to n do
    begin
      ok := true;
      for j := 1 to pas-1 do
        if perm[j] = i then
        begin
          ok := false;
          break;
        end;
      if ok then
      begin
        perm[pas] := i;
        Permutare(pas+1,poz+v[i],suma+r[poz+v[i]]);
      end;
    end;


  end;
end;

begin
  assign(input,'heritage.in'); reset(input);
  assign(output,'heritage.out'); rewrite(output);

  readln(n,m); sum := 0; r[0] := 0;


  for i := 1 to n do
  begin
    read(v[i]);
    sum := sum + v[i];
  end;     readln();

  for i := 1 to m do readln(tr[i].d,tr[i].l);

  arie := 0;
  for i := 2 to m do
  begin
    arie := arie + (tr[i].d-tr[i-1].d)*(tr[i].l+tr[i-1].l)/2;
  end;
  arie := arie / sum;

  next := 2; lant := tr[1].l; pos := tr[1].d;
  for i := 1 to sum-1 do
  begin
    caut := arie;
    while af_aria(pos,lant,tr[next].d,tr[next].l) <= caut do
    begin
      caut := caut - rez;
      lant := tr[next].l; pos := tr[next].d;
      inc(next);
    end;           //am aflat in ce trapez ma aflu

    if caut > 0 then
    begin
      ant := lant;
      lant := sqrt((2*caut*(tr[next].l-lant))/(tr[next].d-pos)+lant*lant);
      dist := 2 * caut / (ant+lant);
      pos := pos+dist;


      add_it(lant,pos);
    end
    else
      add_it(lant,pos);
  end;

  min := 722563929.44567;
  Permutare(1,0,0);

  writeln(min:0:3);
  pos := 0;
  for i := 1 to n-1 do
  begin
    pos := pos + v[rperm[i]];
    write(s[trunc(pos)]:0:2,' ');
  end;


  close(input);
  close(output);
end.
