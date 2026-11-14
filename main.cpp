#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 1e9 + 7;
const int INF =  1e18;
const double pi = acos(-1.0);
const double r = 1737.4;
const double solar = 1361.0;

//int a[301][301];
//const int nas[]={11LL, 101LL, 1001LL, 10001LL, 100001LL, 1000001LL, 10000001LL, 100000001LL, 1000000001LL, 10000000001LL, 100000000001LL, 1000000000001LL, 10000000000001LL, 100000000000001LL, 1000000000000001LL, 10000000000000001LL, 100000000000000001LL, 1000000000000000001LL};
void dsa()
{
    string s;
    bool fl = false;
    double h = 0.002;
    double horizon = -acos(r/(r+h))*180.0/pi;
    vector<string> date;
    vector<double> sazimut;
    vector<double> selevator;
    vector<double> eazimut;
    vector<double> eelevator;
    freopen("sun.txt","r",stdin);
    while(cin>>s)
    {
        if (s == "$$SOE")
        {
            fl = true;
            continue;
        }
        if (s=="$$EOE")
        {
            break;
        }
        if (fl&&(int)s.size()==11&&s.at(4)=='-')
        {
            string l;
            string nxt;
            cin >> l>>nxt;
            double azimut;
            double elevator;
            //cin
            if (!isdigit(nxt.at(0))&&nxt.at(0)!='-')
            {
                cin >> azimut>>elevator;

            }
            else
            {
                azimut = stod(nxt);
                cin>>elevator;
            }
            date.push_back(s+" "+l);
            sazimut.push_back(azimut);
            selevator.push_back(elevator);
        }
    }
    cin.clear();
    freopen("earth.txt","r",stdin);
    fl=false;
    while(cin>>s)
    {
        if (s == "$$SOE")
        {
            fl=true;
            continue;
        }
        if (s == "$$EOE")
        {
            //fl=false;
            break;
        }
        if (fl&&(int)s.size()==11&&s.at(4)=='-')
        {
            string l;
            string nxt;
            cin >> l>>nxt;
            double azimut;
            double elevator;
            //cin
            if (!isdigit(nxt.at(0))&&nxt.at(0)!='-')
            {
                cin >> azimut>>elevator;

            }
            else
            {
                azimut = stod(nxt);
                cin>>elevator;
            }
            eazimut.push_back(azimut);
            eelevator.push_back(elevator);
        }
    }
    int n = min((int) selevator.size(), (int) eelevator.size());
    if (n==0)
    {
        cout<<"Error"<<'\n';
        return;
    }
    int sunh =0;
    int earth=0;
    int optimal = 0;
    int ma=0;
    int cur= 0;
    double tot = 0.0;
    double maelevator = -90.0;
    double mielevator = 90.0;
    vector<int> sunset(n,-1);
    vector<int> earthset(n,-1);
    int lstsun = -1;
    int lstearth = -1;
    for (int i = n -1;i>=0;i--)
    {
        if (selevator[i]<=horizon)
        {
            lstsun = i;
        }
        if (lstsun!=-1)
        {
            sunset[i]=lstsun-i;
        }
        if (eelevator[i]<=horizon)
        {
            lstearth = i;
        }
        if (lstearth!=-1)
        {
            earthset[i]=lstearth-i;
        }
    }
    for (int i = 0; i < n; i++)
    {
        bool sunrise=(selevator[i]>horizon);
        bool earthrise = (eelevator[i]>horizon);
        maelevator = max(maelevator,selevator[i]);
        mielevator = min(mielevator,selevator[i]);
        if (sunrise)
        {
            sunh++;
            cur++;
            if (cur>ma)
            {
                ma = cur;
            }
            tot += solar*sin((selevator[i]-horizon)*pi/180.0);
        }
        else
        {
            cur=0;
        }
        if (earthrise)
        {
            earth++;
        }
        if (sunrise&&earthrise)
        {
            optimal++;
        }
    }
    double mid = 0.0;
    if (sunh>0)
    {
        mid = tot/sunh;
    }
    string sunsetst = "No sunset";
    if (sunset.front()!=-1)
    {
        sunsetst = to_string(sunset.front())+" hours";
    }
    string earthsetst = "No earthset";
    if (earthset.front()!=-1)
    {
        earthsetst=to_string(earthset.front())+" hours";
    }
    string nonest = "Passive";
    if (eelevator.front()>horizon)
    {
        nonest="Active";
    }
    cout << fixed<<setprecision(2);
    cout << "Landing Site - Shackleton Crater (-89.9,0.0 E)"<<'\n';
    cout << "Analysis Period - " << date.front() << " to " << date.back() << " (" << n << " hours)"<<'\n';
    cout << "Effective Horizon Angle - " << setprecision(4) << horizon << " deg " << '\n';

    cout << setprecision(2);
    cout << "Solar Elevation - " << selevator.front() << " deg (Azimuth: " << sazimut.front() << " deg)"<<'\n';
    cout << "Max / Min Solar Elevation - " << maelevator << " / " << mielevator << " deg" << '\n';
    cout << "Total Sunlight Duration - " << sunh << " hours (" << (100.0 * sunh / n) << "%)\n";
    cout << "Longest Continuous Sunlight - " << ma << " hours" << '\n';
    cout << "Average Solar Flux - " << mid << " W/m^2" << '\n';
    cout << "Time to Sunset - " << sunsetst<<'\n';
    cout << "Earth Elevation - " << eelevator.front() << " deg (Azimuth: " << eazimut.front() << " deg)"<<'\n';
    cout << "Direct-to-Earth Comm Duration - " << earth << " hours (" << (100.0 * earth / n) << "%)"<<'\n';
    cout << "Current Comm Status - " << nonest << '\n';
    cout << "Time to Earthset - " << earthsetst << '\n';
    cout << "Optimal Operational Window - " << optimal << " hours (" << (100.0 * optimal / n) << "%)" << '\n';
    freopen("data.js", "w", stdout);
    cout << "const d = [\n";
    for (int i = 0; i < n; i++)
    {
        cout << "{t:'" << date[i] << "',se:" << selevator[i] << ",sa:" << sazimut[i]
             << ",ee:" << eelevator[i] << ",ea:" << eazimut[i] << ",ts:" << sunset[i] << "}";
        if (i < n - 1) cout << ",";
        cout << "\n";
    }
    cout << "];\n";
    }

signed main()
{


    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);

    dsa();

    /**int t;
    cin >> t;
    while(t--)
    {
      dsa();
    }
*/
}


/*

*/
