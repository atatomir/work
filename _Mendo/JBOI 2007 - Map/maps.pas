var i,j,ii,ij,pos,n:longint;
    s:string;

function readd(pos:longint):longint;
begin
  readd := ord(s[pos+1])-$30;
  if (ord(s[pos+2]) >= $30)and(ord(s[pos+2]) <= $39) then
  readd := 10*readd + ord(s[pos+2])-$30;
end;

function dist(i,j,x,y:int64):real;
begin
  dist := (x-i)*(x-i) + (y-j)*(y-j);
  dist := sqrt(dist);
end;

begin
  readln(s); n := length(s);
  s := s + '///';

  i := 0; j := 0; ii := 0; ij := 0;

  for pos := 1 to n do
  begin
    case s[pos] of
      'n': i := i - readd(pos);
      's': i := i + readd(pos);
      'e': j := j + readd(pos);
      'w': j := j - readd(pos);
    end;
  end;

  writeln(dist(i,j,ii,ij):0:2);
end.