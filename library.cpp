//
//  main.cpp
//  Mirror
//
//  Created by 穎川和弘 on 2014/08/08.
//  Copyright (c) 2014年 穎川和弘. All rights reserved.
//
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <complex>
#define MAX_N 1000 //時と場合によって変化
#define MAX_M 1000
#define MAX_V 1000 //頂点数
#define MAX_E 1000 //ブランチ数
using namespace std;


int main(void) {
    int a, m;
    //a / mの結果の端数を切り上げる時~
    //小数点第１位がなんであっても切り上げ
    int ans = (a + m - 1) / m;
    
    //DPで便利な書き方
    (res += dp[r]) % MOD;
    
    //cin -> getline => 空文字列を解決
    cin.ignore();
    
    //文字列連結
    vector<string> ss;
    accmulate(ss.begin(), ss.end(), string()); //vector内の全文字列を連結
    
    //重複除外数
    vector<int> v;
    set<int> (v.begin(), v.end()).size(); //v vector内の重複を除いた数を取得
    
}

//TETORIS
//テトリス
int N;
const int W = 5; //横幅
const int H = 6000; //縦幅 5 * 1000 + α
bool field[H][W]; //盤面

//初期化
void init(){
    //盤面をfalseで埋め尽くす
    for(int i = 0 ; i < H ; i++){
        for(int j = 0 ; j < W ; j++){
            field[i][j] = false;
        }
    }
    // 番兵
    for(int i = 0 ; i < W ; i++){
        field[H-1][i] = true; //最下層はtrueで埋め尽くす
    }
}

//配置
//最大の大きさは５なので、てっぺんに5 * 5の空間を確保する
//指定座標は左端と決まっているから横ならforでx軸方向へtrueで埋めていき、
//縦ならy軸方向へtrueで埋めていく
bool piece[5][5]; //ブロックを確定させる空間
void setPiece(int d,int p){
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            piece[i][j] = false; //空間を初期化
        }
    }
    //空間にブロックを置く
    if(d == 1) for(int i = 0 ; i < p ; i++)piece[4][i] = true;  // 横
    else for(int i = 0 ; i < p ; i++)piece[4 - i][0] = true; // 縦
}

//数え上げ
int count(){
    int cnt = 0;
    for(int i = 0 ; i < H-1 ; i++){ //0 ~ 5998まで //というのも5999の行は番兵が置かれているため
        for(int j = 0 ; j < W ; j++){ //0 ~ 4まで
            if(field[i][j])cnt++; //true=ブロックがある　ので数える
        }
    }
    return cnt; //結果を返す
}

//ブロックを落とすときに使う
bool isCollide(int x,int y){ //0, q-1 => 大きさ5なら(0,4)ということになる
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            int X,Y;
            X = x + j;
            Y = y + i;
            if(X >= 5)continue;
            if(piece[i][j] && field[Y][X])return true; //盤面に配置されたらtrueを返す
        }
    }
    return false;
}


void draw(int x,int y){
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            int X,Y;
            X = x + j;
            Y = y + i;
            if(X >= 5)continue; //X座標は5以上ない（0~4)
            if(piece[i][j])field[Y][X] = piece[i][j]; //盤面に空間上のブロックを反映させる
        }
    }
}

//揃ったら消去
void del(){
    for(int i = 0 ; i < H-1 ; i++){
        bool f = false;
        for(int j = 0 ; j < W ; j++){
            if(!field[i][j])f = true;
        }
        if(f)continue;
        for(int j = 0 ; j < W ; j++)field[i][j] = false;
        for(int j = i-1 ; j >= 0 ; j--){
            for(int k = 0 ; k < W ; k++)field[j+1][k] = field[j][k];
        }
    }
}


void drop(int q){
    int x = q - 1, y = 0;
    
    while(true){
        if(isCollide(x,y)){
            y--;
            draw(x,y);
            del();
            break;
        }
        y++;
    }
}






void solve(){
    for(int i = 0 ; i < N ; i++){ //入力
        int d,p,q;
        cin >> d >> p >> q;
        setPiece(d,p); //ピースをセット
        drop(q); //落とす
    }
    cout << count() << endl; //いくつのブロックで埋められているか
}

int main(){
    while(cin >> N,N){
        init(); //初期化
        solve(); //解決
    }
    return 0;
}




//深さ優先探索
//部分和問題
//整数がいくつか与えられます。その中からいくつか選び、その和をちょうどk
//にする事が出来るか判定しなさい
int a[MAX_N];
int n, k;
//iまででsumを作って、残りi以降を調べる
bool dfs(int i, int sum) {
    //n個決め終わったら、今までの和sumがkと等しいかを返す
    if(i == n) return(sum == k);
    
    //a[i]を使わない場合
    if(dfs(i + 1, sum)) return(true);
    //a[i]を使う場合
    if(dfs(i + 1, sum + a[r])) return(true);
    
    //a[i]を使う使わないに拘らずkが作れないのでfakseを返す
    return(false);
}

void solve() {
    if(dfs(0, 0)) printf("YES\n");
    else          printf("No\n");
}

//Lake Counting
//大きさがN * Mの庭があります。そこに雨が降り、水たまりができました　。水たまりは８近傍で隣接している場合に繋がっているとみなします。全部でいくつの水たまりがあるでしょうか。
//入力
int N, M;
char field[MAX_N][MAX_M + 1]; //庭

//現在位置(x, y)
void dfs(int x, int y) {
    //今いる所を'.'に置き換える
    field[x][y] = '.';
    
    //移動する８方向をループ
    for(int dx = -1; dx <= 1; dx++) {
        for(int dy = -1; dy <= 1; dy++) {
            //x方向にdx、y方向にdyだけ移動した場所を(nx, ny)とする
            int nx = x + dx; int ny = y + dy;
            
            //nxとnyが庭の範囲内かどうかと、field[nx][ny]が水たまりかどうかを判定
            if(nx >= 0 && nx < N && ny >= 0 && ny < M && field[nx][ny] == 'W') dfs(nx, ny);
        }
    }
    return;
}

void lake() {
    int res = 0;
    for(int r = 0; r < N; r++) {
        for(int c = 0; c < M; c++) {
            if(field[r][c] == 'W') {
                //Wが残っているならdfsを始める
                dfs(r, c);
                res++;
            }
        }
    }
    cout << res << endl;
}

//順列生成
bool used[MAX_N];
int perm[MAX_N];

//{0, 1, 2, 3, 4, ... , n - 1}の並び替えn!通りを生成する
void permutation1(int pos, int n) {
    if(pos == n) {
        /*
         permに対する操作
        */
        return;
    }
    
    //permのpos番目を0~n - 1のどれにするかのループ
    for(int r = 0; r < n; r++) {
        if(!used[r]) {
            perm[pos] = r;
            //iを使ったのでフラグをtrueにしておく(要は、１通りの順列を作る時、同じ数字があってはだめだから、
            //trueにしてから処理を行い、１通り生成出来たらused[r] = falseとする)
            used[r] = true;
            permutation1(pos + 1, n); //１通りの順列を完成させる
            //戻って来たらフラグを残しておく
            used[r] = false;
        }
    }
    return;
}

//発展例：カード問題
int cards[10];//1～9までのカードの残り枚数
bool ok;//役が作れたかどうかを記録する

void saiki(int deep){
    if(deep==4){
        ok = true; //役が４つ作れた
        return;
    }
    //連番判定
    for(int r = 0; r <= 7; r++){
        if(cards[r]>0&&cards[r+1]>0&&cards[r+2]>0){
            //used[r] = true;
            cards[r]--;
            cards[r+1]--;
            cards[r+2]--;
            //潜っていく
            saiki(deep+1)
            //used[r] = false;
            cards[r]++;
            cards[r+1]++;
            cards[r+2]++;
        }
    }
    
    //３つグループ判定
    for(int r = 1; r <= 9; r++){
        //同じ数字３つで役が作れるか試す
        if(cards[r]>2){
            //used[r] = true;
            cards[r] -= 3;
            //潜っていく
            saiki(deep+1);
            //used[r] = false;
            cards[r]+=3;
        }
    }
}


//カーリング
int w, h; //width, height
int table[21][21]; //盤面
int ans;

//方向
int dx[] = { 0, 0, -1, 1};
int dy[] = {-1, 1,  0, 0};

//DFS
void dfs(int pos, int x, int y) {
    if (pos >= ans) return; //10より深く潜ったらダメ(問題文より)
    
    //下、上、左、右　全て試す
    for (int r = 0; r < 4; r++) {
        int nx = x + dx[r], ny = y + dy[r];
        
        //continueゾーン
        if (nx < 0 || nx >= w) { continue; } //盤面外はcontinue
        if (ny < 0 || ny >= h) { continue; } //盤面外はcontinue
        if (table[ny][nx] == 1) { continue; } //障害物はcontinue
        
        while(true) {
            if (table[ny][nx] == 3) { //もしゴールだったら深さを記録
                ans = pos;
                return;
            }
            
            nx += dx[r]; ny += dy[r]; //次のマスへ
            
            //盤面外はbreak
            if (nx < 0 || nx >= w) { break; }
            if (ny < 0 || ny >= h) { break; }
            
            //もし障害物だったら
            if (table[ny][nx] == 1) {
                table[ny][nx] = 0; //ぶつかれば障害物は消える
                dfs(pos + 1, nx - dx[r], ny - dy[r]);
                table[ny][nx] = 1; //調べ終わったら元に戻しておく
                break;
            }
        }
    }
}

int main(void){
    while (cin>>w>>h, w|h) {
        int sx, sy;
        for(int r = 0; r < h; r++) {
            for(int c = 0; c < w; c++) {
                cin >> table[r][c];
                if(table[r][c] == 2) {sx = x; sy = y;}
            }
        }
        
        ans = 11; //ありえない深さ (すべらせる回数は最大10であるとかいてある)
        dfs(1, sx, sy);
        if (ans > 10) { ans = -1; } //問題文に反するなら-1を入れる
        cout << ans << endl;
    }
    
    return(0);
}

//幅優先探索
//迷路の最短路
//大きさがN * Mの迷路が与えられます。迷路は通路と壁から出来ており、１ターンに隣接する上下左右４コマの通路へ移動する事が出来ます。スタートからゴールまで移動するのに、必要な最小のターン数を求めなさい。ただし、スタートからゴールまで移動出来ると仮定します。
const int INF = 100000000; //INFINITY...めっちゃ大きい数（処理されない程大きいものでなくてはならない）

//状態を表すクラスpairの場合、typedefしておくと便利
typedef pair<int, int> P;

//入力
char maze[MAX_N][MAX_M + 1]; //迷路を表す文字列の配列
int N, M;
int sx, sy;//スタートの座標
int gx, gy;//ゴールの座標

int d[MAX_N][MAX_M];//各点までの最短距離の配列

//移動４方向のベクトル
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

//(sx, sy)から(gx, gy)への最短距離を求める
//たどり着けないとINF
int bfs() {
    queue<P> que;
    //全ての点をINFで初期化
    for(int r = 0; r < N; r++)
        for(int c = 0; c < M; c++){
            d[r][c] = INF;
        }
            //スタート地点をキューに入れ、その点の距離を０にする
            que.push(P(sx, sy));
            d[sx][sy] = 0; //初期位置は０歩で到達できる
                           //=そこにいるということ
            
            //キューが空になるまでループ
            while(que.size()) {
                //キューの先頭を取り出す
                P p = que.front(); que.pop();
                //取り出して来た状態がゴールなら探索をやめる
                if(p.first == gx && p.second == gy) break;
                //移動４方向をループ
                for(int r = 0; r < 4; r++) {
                    //移動した後の点を(nx, ny)とする
                    int nx = p.first + dx[r], ny = p.second + dy[r];
                    //移動が可能かの判定とすでに訪れた事があるかの判定(d[nx][ny] != INFなら訪れた事がある）
                    if(nx >= 0 && nx < N && ny >= 0 && ny < M && maze[nx][ny] != '#' && d[nx][ny] == INF) {
                        //移動出来るならキューに入れ、その点の距離をpからの距離＋１で確定する
                        que.push(p(nx, ny));
                        d[nx][ny] = d[p.first][p.second] + 1;
                    }
                }
            
        
    }
    return(d[gx][gy]);
}
/*
//priority_queue
int main(void) {
    priority_queue<int> pque;
    
    //要素の追加
    pque.push(3);
    
    //空になるまでループ
    while(!pque.empty()) {
        //最大値の取得及び削除
        cout << pque.top() << endl;
        pque.pop();
    }
}
*/
/*
//set
int main(void) {
    set<int> s;
    
    //要素の追加
    s.insert(1);
    s.insert(3);
    s.insert(5);
    
    //要素の検索
    set<int>::iterator ite;
    ite = s.find(1);
    if(ite == s.end()) cout << "notFound" << endl;
    else               cout << "Found"    << endl;
    
    ite = s.find(2);
    if(ite == s.end()) cout << "notFound" << endl;
    else
    
    if(s.count(3) != 0) cout << "Found" << endl;
    else                cout << "notFound"    << endl;
    
    s.erase(3);
    
    for(ite = s.begin(); ite != s.end(); ite++) {
        cout << *ite << endl;
    }
    
    return(0);
}
*/
//map

int main(void) {
    map<int, const char*> m;
    
    //要素の追加
    m.insert(make_pair(1, "ONE"));
    m.insert(make_pair(10, "TEN"));
    m[100] = "HUNDRED";
    
    //要素の検索
    map<int, const char*>::iterator ite;
    ite = m.find(1);
    puts(ite->second);//ONE
    
    ite = m.find(2);
    if(ite == m.end()) cout << "NOt" << endl;
    else               cout << ite->second << endl;
    
    cout << m[10] << endl;
    
    m.erase(10);
    
    //要素すべてをループ
    for(ite = m.begin(); ite != m.end(); ite++) {
        cout << ite->first << ite->second << endl;
    }
    
    return(0);
}

//素数
//入力は全て正とする
//素数判定O(√n)
bool isPrime(int n) {
    if(n < 2) return(false);
    for(int r = 2; r * r <= n; r++) {
        if(n % r == 0) return(false);
    }
    return(true);
}

//約数の列挙O(√n)
vector<int> divisor(int n) {
    vector<int> res;
    for(int r = 1; r * r <= n; r++) {//1も約数には含まれる
        if(n % r == 0) {
            res.push_back(r);
            //1以外では、割れる数だけではなく、対の割った後の数も登録(r == n / rでなければ)
            if(r * r != n) res.push_back(n / r);
        }
    }
    return(res);
}

//素因数分解O(√n)
//ite->first...基数 ite->second指数
//例：出力された結果が2 2
//                 5 2ならば
//2^2 * 5^2 = 100という意味
//素因数分解の計算内容🔻
//2 100
//2  50
//5  25
//5   5
//    1
map<int, int> prime_factor(int n) {
    map<int, int> res;
    for(int r = 2; r * r <= n; r++) {
        while(n % r == 0) {
            res[r]++; //2がこのwhile文の回数だけ割られたといった記録を残しておく
            n /= r; // 反映させる
        }
    }
    if(n != 1) res[n] = 1;//101等、素数を引数に与えられた場合等は、
    //101 1
    //と表示しなくては行けないので、この調整が必要
    return(res);
}

//オイラーのφ関数
int eulerTotient(int n) {
    int res = n;
    for(int r = 2; r * r <= n; r++) {
        if(n % r == 0) {
            res -= res / r;
            while(n % r == 0) n /= r;
        }
    }
    if(n > 1) res -= res / n;
    return(res);
}

//階乗の末尾の０の数
using namespace std;
int main(void) {
    int n;
    while(cin >> n && n){
        int ans = 0;
        while(n >= 5){
            n /= 5;
            ans += n;
        }
        cout << ans <<endl;
    }
    return(0);
}

//エラトステネスの篩
int prime[MAX_N]; //r番目の素数
bool is_prime[MAX_N + 1]; //is_prime[r]がtrueならrは素数

//n以下の素数の数を返す
int sieve(int n) {
    int p = 0;
    //全てtrueで初期化
    for(int r = 0; r <= n; r++) is_prime[r] = true;
    //0と１は素数ではないのでfalse
    is_prime[0] = is_prime[1] = false;
    
    for(int r = 2; r <= n; r++) {//2,3,4,5,6...,n
        if(is_prime[r]) {//もし、素数があれば
            prime[p++] = r;//配列primeに添字(対象となる数)を追加記録しておく
            //🔻
            //r = 2の時
            //4 6 8 10 12...
            //r = 3の時
            //6 9 12 15 18 21 24 27 30...
            for(int c = 2 * r; c <= n; c += r) is_prime[c] = false;//その倍数は素数ではない
        }
    }
    return(p);//p番まで添え字格納したよ〜
}

//区間エラトステネスの篩
typedef long long ll;
bool is_prime[MAX_L];
bool is_prime_small[MAX_SQRT_B];

//[a, b]の整数に対して古いを行う。is_prime[r - a] = true　⇔  rが素数
void segment_sieve(ll a, ll b) {
    //√b分だけの数字について、trueを入れておく(最低限のエラトステネス)
    for(int r = 0; (ll)r * r < b; r++) is_prime_small[r] = true;
    //区間[0,b-a)の範囲について、すべてtrueにして準備しておく(求めたい区画)
    for(int r = 0; r < b - a; r++) is_prime[r] = true;
    
    for(int r = 2; (ll)r * r < b; r++) {
        if(is_prime_small[r]) {
            for(int c = 2 * r; (ll)c * c < b; c += r) is_prime_small[c] = false; //[2,√b)の篩
            for(ll c = max(2LL, (a + r - 1) / r) * r; c < b; c += r) is_prime[c - a] = false;//[a,b)の篩
        }
    }
}

//冪乗の高速計算
//通常関数を用いて実装
typedef long long ll;

ll mod_pow(ll x, ll n, ll mod) {
    ll res = 1;
    while(n > 0) {
        if(n & 1) res = (res * x) % mod; //最下位ビットが立っているときにx^(2^r)を掛ける
        x = (x * x) % mod; //xを順次二乗していく
        n >>= 1; //右論理シフト
    }
    return(res);
}

//再帰関数を用いて実装
ll mod_pow(ll x, ll n, ll mod) {
    if(n == 0) return(1);
    ll res = mod_pow(x * x % mod, n / 2, mod);
    if(n & 1) res = res * x % mod;
    return(res);
}

//最大公約数
//ユークリッドの互除法
int gcd(int a, int b) {
    if(b == 0) return(a);
    return(gcd(b, a % b));
}

//最小公倍数
int lcm(int m, int n) {
    if(m == 0 || n == 0) {//どちらかが０ならば、公倍数など無い
        return(0);
    }
    return(m * n / gcd(m, n));
}

//拡張ユークリッドの互除法
//問題双六を参照
//見ればわかるが、第１引数、第２引数ではgcdを行っているので、b = 0になる時がでてくる。その時にx = 1, y = 0とセットされる


//ax + by = 1という等式において、
//y - (a / b) * xというのは
//gcd(a, b) = gcd(b, a % b) = bx + (a % b)y
//
int extgcd(int a, int b, int& x, int& y) {
    int d = a;
    if(b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x; //->ここだけがよう分からん
    } else {
        x = 1; y = 0;//自然とa * 1 + b * 0 = 1になる
    }
    return(d);
}
int main(void) {
    int x, y;
    
    cout << extgcd(4, 11, x, y) << endl;
    cout << x << ", " << y << endl;
    
    
    return(0);
}

vector<string> split(string &str, char delim){
    stringstream ss(str);
    string tmp;
    vector<string> res;
    while(getline(ss, tmp, delim)) res.push_back(tmp);
    return res;
}


//10進数->n進数への変換
//やってることは普段の計算と相違ない
//例えば10進数の10を2進数に変換したい時、通常ならば
//2 | 10
//2 | 5 ・・・0
//2 | 2 ・・・1
//2 | 1 ・・・0
//    0 ・・・1
//と計算する
//このプログラムのリストだと
//  vector<int>& coef(  |0 | 1 | 0 | 1|   )が返される
//答えは1010で、逆から読めば良いということになる
void toNAdic(unsigned int decimal, vector<int>& coef, int base) {
    do {
        unsigned int c = decimal % base;
        coef.push_back(c);
        decimal /= base;
    } while(decimal != 0);
}

//n進数->10進数への変換
//上のtoNAdic関数と同様に考えてみる
//２進数の1010を10進数(答えは10である)にしたい時、
//変数uは1, 2, 4, 8, 16, ・・・と変化していく
//引数に渡されるvectorの中身は(|0|1|0|1|)の想定であり、
//最初から計算していくとresultは
//(0 * 1) + (1 * 2) + (0 * 4) + (1 * 8) = 10
//となる
unsigned int toDecimal(const vector<int>& coef, int base) {
    unsigned int result = 0, u = 1;
    vector<int>::const_iterator ite;
    for(ite = coef.begin(); ite != coef.end(); ite++) {
        result += *ite * u;
        u *= base;
    }
    return(result):
}

//組み合わせ
//unsigned long long なので大変である
//n - rというのは、例えば5C3の時に
//5 - 3という計算を行う
//r == 0の時は例えば5C0の時なので答えは必然的に１
//それいがいの時には、上の例だと
//分子 = 5 * 4 * 3
//分母 = 1 * 2 * 3
int combination(int n, int r) {
    int parent = 1, child = 1;
    for(int c = n; c >= r; c--) parent *= c; // 5 * 4 * 3
    for(int c = 2; c <= r; c++) child *= c;
    return(parent / child);
}
//順列
unsigned long long permutation(unsigned long long n, unsigned long long r) {
    unsigned long long result = 1;
    for(unsigned long long r = n; r > n - r; r--)result *= r;
    return(result);
}

int permutation(int n, int r) {
    int ret = 1;
    for(int c = r; c <= n; c++) ret *= c;
    return(ret);
}

//グレイ符号
//val ・・・　変換したい２進数
unsigned int GrayCode(unsigned int val) {
    return( val ^ (val >> 1));
}



//Union-Find木
int par[MAX_N]; //親
int _rank[MAX_N];//木の深さ

//n要素で初期化
void init(int n) {
    for(int r = 0; r < n; r++) {
        par[r] = r; _rank[r] = 0;
    }
}

//木の根を求める
int find(int x) {//処理が進むと、par[par[par[par[x]]]]みたいな具合になる。要は、親要素を辿って行く
    if(par[x] == x) return(x);//親が自分である=ルート要素である
    else            return(par[x] = find(par[x]));
}

//xとyの属する集合を併合
//高さに差がある場合、高い方の木に併合され、高さはその木に依存するが、高さが同じ場合、１だけ高くなる
void unite(int x, int y) {
    x = find(x); y = find(y); //それぞれのルートを検索
    if(x == y) return;//同じルートであれば、既に併合されている事になる
    
    //以下、併合されていない場合の処理
    if(_rank[x] < _rank[y]) par[x] = y; //rankについて、yの属する木の方が、xの属する木よりも高いならば、xの親要素はyとなる
    else { //xとy、木の高さを比較して、yの方が高いか、どちらも高さが同じ場合
        par[y] = x; //yの親要素はxとなる
        if(_rank[x] == _rank[y]) _rank[x]++; //高さが同じだった場合、木の深さが１だけ深くなる
    }
}

//xとyが同じ集合に属するか否か
//ルート要素を比較して、同じであれば同じ集合、そうでなければ違う集合となる
bool same(int x, int y) {
    return(find(x) == find(y));
}


//upper_bound, lower_boundの基本的な使い方
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
    vector<int> data;
    
    //0~18まで２の倍数を格納{0, 2, 4, 6, 8, 10, 12, 14, 16, 18}
    for(int r = 0; r < 10; r++) data.push_back(r * 2);
    //7以上の最初の要素を求める
    vector<int>::iterator it1 = lower_bound(data.begin(), data.end(), 7);
    //7より大きい要素を求める
    vector<int>::iterator it2 = upper_bound(data.begin(), data.end(), 7);
    
    //8以上の最初の要素を求める
    vector<int>::iterator it3 = lower_bound(data.begin(), data.end(), 8);
    //8より大きい要素を求める
    vector<int>::iterator it4 = upper_bound(data.begin(), data.end(), 8);
    
    cout << "lower_bound(7):" << *it1 << endl;
    cout << "upper_bound(7):" << *it2 << endl;
    cout << "lower_bound(8):" << *it3 << endl;
    cout << "upper_bound(8):" << *it4 << endl;
    
}

//単一視点最短路問題１(ベルマンフォード法）・・・負閉路大丈夫、しかも検知してくれる
//例えば、データ量が多い・・・ワーシャルフロイドは不可
//負の閉路がある・・・ダイクストラが使用不可の状況下等でつかう
struct edge {
    int from;
    int to;
    int cost;
};
edge es[MAX_E];
int d[MAX_V]

int V, E;

bool shortest_path(int s){
    memset(d, 0, sizeof(d));
    d[s] = 0;
    for(int r = 0; r < V + 1; r++) {
        bool update = false;
        for(int c = 0; c < E; c++) {
            edge e = es[c];
            if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                if(r == V) return(false);
                
                update = true;
            }
        }
    }
    return(true);
}

//単一始点最短路問題２　ダイクストラ法・・・ワーシャルフロイドで扱えない問題（とても頂点数が多い等）に使う
//ベルマンフォード法よりも計算量が少ないので、実装出来るならダイクストラにした方が良い

//STLを使わない実装(少し分かりにくい・・・)
/*
int cost[MAX_V][MAX_V]; //cost[u][v]は辺e = (u, v)のコスト(存在しない場合はINF)
int d[MAX_V]; //頂点sからの最短距離
bool used[MAX_V];　//既に使われたかのフラグ
int V; //頂点数

void dijkstra(int s) {
    fill(d, d + V, INF); //最短距離を全てINF(膨大な数)にする
    fill(used, used + V, false);//使用しているかを全てfalseに初期化
    d[s] = 0;//スタート地点は最短距離０
    
    while(true) {
        int v = -1;
        //まだ使われていない頂点のうち距離が最短のものを探す
        for(int u = 0; u < V; u++) {
            //使われていないかつ、最初か、格納値より小さいときに最小値を変更
            if(!used[u] && (v == -1 || d[u] < d[v])) v = u;
        }
        if(v == -1) break; //何も処理が行われていないから、抜け出し
        used[v] = true;//これから使う
        for(int u = 0; u < V; u++) {
            //最短距離を決める（今の格納値か、今見ている頂点からコストを足したものの距離か)
            d[u] = min(d[u], d[v] + cost[v][u]);
        }
    }
}
*/
//STL(priority_queue)を使った実装
//幅優先探索みたいな具合に書ける
struct edge {
    int to;
    int cost;
};
typedef pair<int, int> P; //firstは最短距離、secondは頂点の番号

int V; //頂点数
vector<edge> G[MAX_V]; //辺を格納した可変配列
int d[MAX_V]; //最短距離

void dijkstra(int s) {
    //greater<V>を指定する事でfirstが小さい順に取り出せる様にする
    priority_queue<P, vector<P>,greater<P>> que;
    fill(d, d + V, INF); //最短距離をINFで埋めておく
    d[s] = 0;//初期位置の最短距離は０ 最短距離配列dを更新
    que.push(P(0, s)); //初期位置は０歩でたどり着く 調べる先queを更新
    
    while(!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second;
        if(d[v] < p.first) continue;//最短距離(初期INFの配列d)を比べ、初期値であるはずのINFよりも大きい（つまり、既に更新されていて、かつ今見ている距離よりも短いものであれば、更新する必要は無い(-> INFだったら無視)
            //なぜならば、
        for(int r = 0; r < G[v].size(); r++) {
            edge e = G[v][r];
            //更新する必要のある頂点vから行ける場所
            //Graph[更新する必要のある頂点][行ける場所(r = 0,1,2...G[v].size())]
            if(d[e.to] > d[v] + e.cost) {//試す頂点２つに対して、更新した方が良いか否か確かめ、更新を行う
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}

//全点対最短路問題（ワーシャル・フロイド法)
int d[MAX_V][MAX_V]; //d[u][v]は辺e = (u, v)のコスト（存在しない場合はINF、ただしd[i][i] = 0とする）
int V;//頂点数

bool warshall_floyd() {
    for(int via = 0; via < V; via++) { //経由
        for(int from = 0; from < V; from++) { //初期地点
            for(int to = 0; to < V; to++) {　//目的地
                d[from][to] = min(d[from][to], d[from][via] + d[via][to]);
            }
        }
    }
    for(int r = 0; r < V; r++) {
        if(d[r][r] < 0) return(false);
    }
    return(true);
}

//01ナップザック問題
int dp[MAX_N + 1][MAX_W + 1]; //DPテーブル

void solve() {
    for(int r = n - 1; r >= 0; r--) {
        for(int c = 0; c <= W; c++) {
            if(c < w[r]) {
                dp[r][c] = dp[r + 1][c];
            } else {
                dp[r][c] = max(dp[r + 1][c], dp[r + 1][c - w[r]] + v[r]);
            }
        }
    }
    printf("%d\n", dp[0][W]);
}

//最長共通部分列問題
int n, m;
char s[MAX_N], t[MAX_M];

int dp[MAX_N + 1][MAX_M + 1];


/* S1...Si+1とT1...Tj+1に対する共通部分列は... */
//Si+1 = Ti+1ならば、S1...SiとT1...Tjに対する共通部分列の後ろにSi+1をつなげたもの
//S1...SiとT1...Tj+1に対する共通部分文字列
//S1...Si+1とT1...Tjに対する共通部分文字列

void solve() {
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            if(s[r] == t[c]) {
                dp[r + 1][c + 1] = dp[r][c] + 1;
            } else {
                //一致しないならば変化は起こらない
                //=上からか、下からの遷移で大きい方を取る
                dp[r + 1][c + 1] = max(dp[r + 1][c], dp[r][c + 1]);
            }
        }
    }
    printf("%d\n", dp[n][m]);
}

//個数制限無しナップザック問題
int n, W;

void solve() {
    for(int r = 0; r < n; r++) {
        for(int c = 0; c <= W; c++) {
            for(int k = 0; k * w[r] <= c; k++) { // * kがついただけ
                dp[r + 1][c] = max(dp[r][c], dp[r][c - k * w[r]] + k * v[r]);
            }
        }
    }
}

/* 高速（今は手をつけなくていい）
void solve() {
    for(int r = 0; r < n; r++) {
        for(int c = 0; c <= W; c++) {
            if(c < w[r]) {
                dp[r + 1][c] = dp[r][c];
            } else {
                dp[r + 1][c] = max(dp[r][c], dp[r + 1][c - w[r]] + v[r]);
            }
        }
    }
    printf("%d\n", dp[n][W]);
}
*/


#define EPS (1e-10) // 許容する誤差ε
#define EQ(a,b) (abs((a)-(b)) < EPS)// 2つのスカラーが等しいかどうか
#define EQV(a,b) ( EQ((a).real(), (b).real()) && EQ((a).imag(), (b).imag()) ) // 2つのベクトルが等しいかどうか

typedef complex<double> P;

// ベクトルaの絶対値を求める
double length = abs(a);

// 2点a,b間の距離を求める
double distance = abs(a-b);

// ベクトルaの単位ベクトルを求める
P b = a / abs(a);

// ベクトルaの法線ベクトルn1,n2を求める
P n1 = a * P(0, 1);
P n2 = a * P(0, -1);

// ベクトルaの単位法線ベクトルun1,un2を求める
P un1 = (a * P(0, +1)) / abs(a);
P un2 = (a * P(0, -1)) / abs(a);

// 内積 (dot product) : a・b = |a||b|cosΘ
double dot(P a, P b) {
    return (a.real() * b.real() + a.imag() * b.imag());
}

// 外積 (cross product) : a×b = |a||b|sinΘ
double cross(P a, P b) {
    return (a.real() * b.imag() - a.imag() * b.real());
}

// 2直線の直交判定 : a⊥b <=> dot(a, b) = 0
int is_orthogonal(P a1, P a2, P b1, P b2) {
    return EQ( dot(a1-a2, b1-b2), 0.0 );
}

// 2直線の平行判定 : a//b <=> cross(a, b) = 0
int is_parallel(P a1, P a2, P b1, P b2) {
    return EQ( cross(a1-a2, b1-b2), 0.0 );
}

//ここから難易度がちょび上がる

// 点cが直線a,b上にあるかないか
int is_point_on_line(P a, P b, P c) {
    return EQ( cross(b-a, c-a), 0.0 );
}

// 点cが線分a,b上にあるかないか(2)
int is_point_on_line(P a, P b, P c) {
    // |a-c| + |c-b| <= |a-b| なら線分上
    return (abs(a-c) + abs(c-b) < abs(a-b) + EPS);
}

//更に上がる

// 点a,bを通る直線と点cとの距離
//x × y = |x||y|sinθ
//(x × y) / |x| = |y|sinθ(=d)
//よって、d = (x × y) / |x|
double distance_l_p(P a, P b, P c) {
    return abs(cross(b-a, c-a)) / abs(b-a);
}

// 点a,bを端点とする線分と点cとの距離
double distance_ls_p(P a, P b, P c) {
    //直線a-b, a-cが直行するなら、距離はc-aで良い
    if ( dot(b-a, c-a) < EPS ) return abs(c-a);
    //直線a-b, c-bが直行するなら、距離はc-bで良い
    if ( dot(a-b, c-b) < EPS ) return abs(c-b);
    
    //そうでなければ、上のdistance_l_pを返す
    return abs(cross(b-a, c-a)) / abs(b-a);
}

//こっからもっと上がります

// a1,a2を端点とする線分とb1,b2を端点とする線分の交差判定
//点が線分の左側（sinθは0~180で正）ならば正である
//逆に、点が線分の右側(sinθは181~359で負)ならば負である
//つまり、ある直線a1-a2を基準とし、
//b1, b2のそれぞれをテストする
//b1が右、b2が左、もしくはb1が左、b2が右ならば
//外積の積は正　x  負 = 負となるはずである
int is_intersected_ls(P a1, P a2, P b1, P b2) {
    return ( cross(a2-a1, b1-a1) * cross(a2-a1, b2-a1) < EPS ) &&
    ( cross(b2-b1, a1-b1) * cross(b2-b1, a2-b1) < EPS );
}

// a1,a2を端点とする線分とb1,b2を端点とする線分の交点計算
//(交差前提)
P intersection_ls(P a1, P a2, P b1, P b2) {
    P b = b2-b1;
    double d1 = abs(cross(b, a1-b1)); //a2から直線b1-b2に下ろした垂線の長さ
    double d2 = abs(cross(b, a2-b1)); //a1から直線b1-b2に下ろした垂線の長さ
    double t = d1 / (d1 + d2);//垂線の合計長のd1の割合
    
    return a1 + (a2-a1) * t;
}

// a1,a2を通る直線とb1,b2を通る直線の交差判定
int is_intersected_l(P a1, P a2, P b1, P b2) {
    //a1-a2とb1-b2が平行でなければ、直線である限り必ずどっかで交差
    return !EQ( cross(a1-a2, b1-b2), 0.0 );
}

// a1,a2を通る直線とb1,b2を通る直線の交点計算
P intersection_l(P a1, P a2, P b1, P b2) {
    P a = a2 - a1; P b = b2 - b1; //直線a1-a2, b1-b2
    return a1 + a * cross(b, b1-a1) / cross(b, a);
}



//条件に合わないと、強制的に(lldb)にしてエラー文を表示させる
/*
#include <cassert>
int main(void) {
    int a = 5;
    int b = 3;
    
    assert(b - a > 0);
    cout << a << b << endl;
    
    return(0);
}
*/

           
           














