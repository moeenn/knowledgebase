```bash
$ npm i jsonwebtoken zod
$ npm i -D @types/jsonwebtoken
```

```js
import jwt from "jsonwebtoken"
import { z } from "zod"

/**
 * @typedef {"admin" | "user"} UserRole
 * 
 * @typedef User
 * @property {string} user_id
 * @property {string} email
 * @property {UserRole} role
 */

/**
 * @typedef SessionToken
 * @property {string} accessToken
 * @property {string} refreshToken
 * @property {number} expiry
 */

/**
 * @typedef JWTEncoded
 * @property {string} token
 * @property {number} expiry
 */

const SESSION_REFRESH_TOKEN_SCOPE = "session.refresh"
const SESSION_ACCESS_TOKEN_SCOPE = "session.access"

class SessionRefreshToken {
  /** @type {string} */
  userId

  /** @type {string} */
  email

  /** @type {UserRole} */
  role

  /** @type {string} */
  scope

  /**
   * @param {string} userId 
   * @param {string} email 
   * @param {UserRole} role 
   */
  constructor(userId, email, role) {
    this.userId = userId
    this.email = email
    this.role = role
    this.scope = SESSION_REFRESH_TOKEN_SCOPE
  }

  /**
   * @returns {JWTEncoded}
   */
  encode() {
    const token = JWT.generateNonExpiringToken({
      userId: this.userId,
      email: this.email,
      role: this.role,
      scope: this.scope,
    })

    return { token, expiry: -1 }
  }

  /**
   * @param {unknown} payload 
   * @returns {SessionRefreshToken | undefined}
   */
  static #validatePayload(payload) {
    const schema = z.object({
      userId: z.string().uuid(),
      email: z.string().email(),
      role: z.enum(["admin", "user"]),
      scope: z.literal(SESSION_REFRESH_TOKEN_SCOPE)
    })

    const v = schema.safeParse(payload)
    if (!v.success) {
      return
    }

    return new SessionRefreshToken(
      v.data.userId,
      v.data.email,
      v.data.role
    )
  }

  /**
   * @param {string} token 
   * @return {SessionRefreshToken | undefined}
   */
  static validate(token) {
    try {
      const payload = jwt.verify(token, config.jwt.secret)
      if (typeof payload == "string") return
      return SessionRefreshToken.#validatePayload(payload)
    } catch { }
  }
}

class SessionAccessToken extends SessionRefreshToken {
  /** @type {number} */
  expiry

  /** @type {string} */
  scope

  /**
   * @param {string} userId 
   * @param {string} email 
   * @param {UserRole} role 
   */
  constructor(userId, email, role) {
    super(userId, email, role)
    this.scope = SESSION_ACCESS_TOKEN_SCOPE
    this.expiry = JWT.calculateExpiry()
  }

  /**
   * @returns {JWTEncoded}
   */
  enodeWithExpiry() {
    return JWT.generateExpiringToken({
      userId: this.userId,
      email: this.email,
      role: this.role,
      scope: this.scope,
    })
  }

  /**
   * @param {unknown} payload 
   * @returns {SessionAccessToken | undefined}
   */
  static #validatePayload(payload) {
    const schema = z.object({
      userId: z.string().uuid(),
      email: z.string().email(),
      role: z.enum(["admin", "user"]),
      scope: z.literal(SESSION_ACCESS_TOKEN_SCOPE)
    })

    const v = schema.safeParse(payload)
    if (!v.success) {
      return
    }

    return new SessionAccessToken(
      v.data.userId,
      v.data.email,
      v.data.role
    )
  }

  /**
   * @param {string} token 
   * @return {SessionAccessToken | undefined}
   */
  static validate(token) {
    try {
      const payload = jwt.verify(token, config.jwt.secret)
      if (typeof payload == "string") return
      return SessionAccessToken.#validatePayload(payload)
    } catch { }
  }
}

export class JWTFactory {
  /**
   * create access and refresh tokens for the user at successful login
   * 
   * @param {User} user 
   * @returns {SessionToken}
   */
  static generateSessionToken(user) {
    const accessPayload = new SessionAccessToken(user.user_id, user.email, user.role).enodeWithExpiry()
    const refreshPayload = new SessionRefreshToken(user.user_id, user.email, user.role).encode()

    return {
      accessToken: accessPayload.token,
      expiry: accessPayload.expiry,
      refreshToken: refreshPayload.token,
    }
  }
}

export class JWT {
  /**
   * calculate expiry timestamp for the client
   * @returns {number}
   */
  static calculateExpiry() {
    return Math.floor(Date.now() / 1000) + (60 * 60 * config.jwt.expiresInHours)
  }

  /**
   * @param {object} payload 
   * @returns {JWTEncoded}
   */
  static generateExpiringToken(payload) {
    const token = jwt.sign(payload, config.jwt.secret, {
      expiresIn: (60 * 60 * config.jwt.expiresInHours),
      notBefore: "0",
      algorithm: config.jwt.algorithm,
      issuer: config.jwt.issuer,
    })

    const expiry = this.calculateExpiry()
    return { token, expiry }
  }

  /**
   * @param {object} payload 
   * @returns {string}
   */
  static generateNonExpiringToken(payload) {
    return jwt.sign(payload, config.jwt.secret, {
      notBefore: '0',
      algorithm: config.jwt.algorithm,
      issuer: config.jwt.issuer,
    })
  }
}

const config = {
  jwt: {
    secret: "super-secret-secret",
    expiresInHours: 1,
    algorithm: /** @type {jwt.Algorithm} */ ('HS256'),
    issuer: 'host.com',
  },
}

/** @returns {Promise<void>} */
async function main() {
  /** @type {User} */
  const user = {
    user_id: crypto.randomUUID(),
    email: "user@site.com",
    role: "admin",
  }

  const payload = JWTFactory.generateSessionToken(user)

  const accessToken = SessionAccessToken.validate(payload.accessToken)
  console.log(JSON.stringify(accessToken))

  const refreshToken = SessionRefreshToken.validate(payload.refreshToken)
  console.log(JSON.stringify(refreshToken))
}

main()
```