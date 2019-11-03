char s[M];
struct SuffixAutomata{
    
    int par[M],son[M][26],maxlen[M],endpos[M],pos[M],minlen[M];

    int root,last,cur;
	long long cnt;

    int NewNode(int len){
        maxlen[cur]=len;
        minlen[cur]=0;
        endpos[cur]=0;
        pos[cur]=0;
        par[cur]=0;
        memset(son[cur],0,sizeof son[cur]);
        return cur++;
    }
    void init(){
        cur=1;
        last=root=NewNode(0);
    }

    
	void Extend(int x,int pp){
		int p=last,nx=NewNode(maxlen[last]+1);
        endpos[nx]=pos[nx]=pp;
		for(;p&&!son[p][x];son[p][x]=nx,p=par[p]);
		if(p==0){
			par[nx]=root;
		}else{
			int ox=son[p][x];
			if(maxlen[p]+1==maxlen[ox]){
				par[nx]=ox;
			}else{
				int o=NewNode(maxlen[p]+1);
                pos[o]=pos[ox];
                par[o]=par[ox];
                memcpy(son[o],son[ox],sizeof son[o]);
				par[ox]=par[nx]=o;
				for(;p&&son[p][x]==ox;son[p][x]=o,p=par[p]);
			}
		}
		cnt+=maxlen[nx]-maxlen[par[nx]];
		last=nx;
	}
    void Build(){
        static int c[M],id[M],v[30];
        v[0]=2;
        for(int i=1;i<=26;++i)
            v[i]=0;
        for(int i=2;i<cur;++i){
            minlen[i]=maxlen[par[i]]+1;
            c[i]=s[pos[i]+minlen[i]-1]-'a'+1;
            ++v[c[i]];
        }
        for(int i=1;i<=26;++i){
            v[i]+=v[i-1];
        }
        for(int i=2;i<cur;++i){
            id[--v[c[i]]]=i;
        }

        for(int i=2;i<cur;++i){
            e[par[id[i]]].push_back(id[i]);
        }
    }
}sam;
