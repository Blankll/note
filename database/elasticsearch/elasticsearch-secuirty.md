# Elasticsearch安全概述

   Elasticsearch 的安全机制涵盖多种层面的配置和策略，旨在保护数据的传输、存储及访问控制。这些机制包括加密、身份认证、访问权限控制和审计记录，能够有效地防止数据泄露、未经授权的访问以及操作误用。以下内容将逐步介绍 Elasticsearch 安全的主要方面及其具体实现。

---


   ###  加密（Encryption）

   Elasticsearch 中的加密包含**传输加密**和**静态数据加密**（加密落盘）。在数据传输过程中，Elasticsearch 使用 TLS 协议对客户端与服务器、服务器节点之间的数据传输进行加密，从而防止数据在传输中被拦截。静态数据加密则是在数据写入磁盘时进行加密，这样即使服务器被入侵，黑客也只能获得加密后的数据，从而提升数据安全性。

   ### 身份认证（Authentication）

   Elasticsearch 支持多种身份认证方式，以适应不同的安全需求：

   - **Basic Authentication（基本认证）**：使用用户名和密码进行认证。通常通过 X-Pack 插件来启用。
   - **API Key Authentication（API 密钥认证）**：使用 JSON Web Token (JWT) 来创建 API 密钥，从而让应用与 Elasticsearch 交互时不必暴露实际凭证。
   - **OAuth 2.0 / OpenID Connect（单点登录）**：通过 OAuth 2.0 或 OpenID Connect 协议集成第三方身份提供商（如 Google、Azure AD），实现单点登录。
   - **SAML（Security Assertion Markup Language）**：通过 SAML 协议集成企业身份管理系统，如 Okta、Ping Identity 等。
   - **Kerberos**：基于 Kerberos 协议的认证方式，适合与 Active Directory 集成的企业网络。
   - **PKI（Public Key Infrastructure）认证**：通过客户端证书认证，依赖公钥基础设施（PKI），适用于对安全性要求极高的场景。
   - **LDAP（Lightweight Directory Access Protocol）**：通过 LDAP 协议连接企业目录服务（如 Microsoft AD），便于内部用户和组的管理。

   这些认证方式可以组合使用，以满足复杂的安全需求。

   ### 访问权限控制（Access Control）

   在 Elasticsearch 中，通过**基于角色的访问控制**（RBAC）来管理用户权限，从而确保数据和操作的安全性。RBAC 涉及以下几个概念：

   #### 用户（User）
   用户是在 Elasticsearch 中执行操作的主体，可以是实际用户或应用程序。每个用户都有唯一标识（用户名）和凭证（如密码或 API 密钥）。权限分配基于角色，而非直接赋予用户。

   #### 用户角色（Role）
   角色是权限的集合，定义了用户对特定资源的操作权限（如读、写、管理）。一个用户可拥有多个角色，其权限会综合计算。

   #### 资源（Resource）
   资源是 Elasticsearch 中受保护的实体，主要包括：
   - **索引（Index）**：存储实际数据的逻辑分区，可以配置独立权限。
   - **文档（Document）**：索引中的具体数据记录，可进一步细化权限控制（如只读权限）。
   - **集群（Cluster）**：包括管理集群状态、节点管理等。RBAC 可限制用户执行特定集群操作。

   #### 权限（Permission）
   权限定义可执行的操作类型，包括集群级权限、索引级权限、文档级权限和字段级权限。权限设置支持细粒度控制，例如：
   - **集群级权限**：管理集群和索引的操作权限（如 `monitor`、`manage`）。
   - **索引级权限**：特定索引的操作权限（如读 `read`、写 `write`、删除 `delete`）。
   - **文档级权限（DLS）**：限制用户访问特定类型的文档。
   - **字段级权限（FLS）**：限制用户对特定字段的访问或修改权限。

   这种灵活的配置方式确保了数据的安全性和操作的合规性。

   ###  审计日志与合规（Audit Logging and Compliance）

   审计日志记录 Elasticsearch 中的安全相关事件，包括身份验证、授权失败、用户操作等。通过启用审计日志，可以跟踪并监控敏感数据访问及不合规操作，以确保系统符合安全及合规要求。

---

   ### 匿名认证（Anonymous Authentication）

   Elasticsearch 允许启用匿名认证，为不带认证信息的用户分配一个默认角色（`anonymous_users_role`）。通过该角色，可以为匿名用户配置有限的权限（如只读），使公司内部用户在无需登录的情况下即可访问某些数据或集群状态。

   #### 优势
   匿名认证有助于控制内部访问。例如，通过公司 VPC 管控 Elasticsearch 的内部访问，再为匿名用户配置只读权限，避免数据误操作。而应用程序则可以使用特定的用户和角色来获得所需权限，这样实现了应用程序与运维/开发权限的分离。

   #### 开启匿名认证

   以下是开启匿名认证的步骤：

   1. 修改 Elasticsearch 服务的 `opensearch_dashboards.yml` 配置：
   
      ```yaml
      http:
        anonymous_auth_enabled: true
      ```
   
   2. 修改 Kibana 的 `config.yml` 配置：
   
      ```yaml
      opensearch_security.auth.anonymous_auth_enabled: true
      ```
   
   3. 配置匿名用户的权限：
   
      在 `roles.yml` 文件中，为匿名用户配置相应的权限：
   
      ```yaml
      anonymous_users_role:
        reserved: false
        hidden: false
        cluster_permissions:
        - "OPENDISTRO_SECURITY_CLUSTER_COMPOSITE_OPS"
        index_permissions:
        - index_patterns:
          - "public_index_*"
          allowed_actions:
          - "read"
      ```
   
      在 `roles_mapping.yml` 文件中，将 `anonymous_users_role` 绑定至相应的角色：
   
      ```yaml
      anonymous_users_role:
        reserved: false
        hidden: false
        backend_roles: ["opendistro_security_anonymous_backendrole"]
        hosts: []
      ```

   通过以上配置，Elasticsearch 可以为匿名用户提供受限访问，确保基础安全性的同时简化内部访问。