# spring security

install

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-security</artifactId>
</dependency>
```

configuration - extends `WebSecurityConfigurerAdapter` and rewrite configure method

```java
@EnableWebSecurity
public class SecurityContext extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(AuthenticationManagerBuilder auth) throws Exception { }
    @Override
    public void configure(HttpSecurity http) throws Exception {}
}
```

create `SecurityUserDetailService` implement `UserDetailService` it use to load a user from existing system by name, email, id,etc

```java
@Service
public class SecurityUserDetailService implements UserDetailsService {
    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        return new User("blank", "0707", new ArrayList<>());
    }
}
```

controller validate user info & generate token

```java
@PostMapping("/authenticate")
    public Resp<String> login(@Valid UserLoginRequest loginRequest) throws ExternalException {
        try {
        authenticationManager.authenticate(
                new UsernamePasswordAuthenticationToken(
                        loginRequest.getUsername(),
                        loginRequest.getPassword())
        );
        } catch (BadCredentialsException e) {
            throw new ExternalException(ExceptionEnum.USER_NOT_EXISTS);
        }
        UserDetails userDetails = userDetailService.loadUserByUsername(loginRequest.getUsername());
        String token = jwtUtil.getToken(loginRequest.getUsername());

        return new Resp<String>(token);
    }
```

use filter to validate user token

```java

```

